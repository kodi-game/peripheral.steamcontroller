/*
 *      Copyright (C) 2016 Garrett Brown
 *      Copyright (C) 2016 Team Kodi
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this Program; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "USBDeviceHandle.h"
#include "USBTransfer.h"
#include "usb/interfaces/IMessageCallback.h"
#include "util/Log.h"

#include <algorithm>
#include <assert.h>
#include <libusb.h>
#include <unistd.h>
#include <utility>

using namespace STEAMCONTROLLER;

CUSBDeviceHandle::CUSBDeviceHandle(libusb_device_handle* handle) :
  m_handle(handle)
{
  assert(m_handle != nullptr);
}

CUSBDeviceHandle::~CUSBDeviceHandle()
{
  Close();
}

void CUSBDeviceHandle::Close()
{
  for (auto it = m_transfers.begin(); it != m_transfers.end(); ++it)
    it->first->Doom();

  for (auto& transfer : m_inflightTransfers)
    transfer->Cancel();

  while (!m_inflightTransfers.empty())
    usleep(10);

  for (auto it = m_transfers.begin(); it != m_transfers.end(); ++it)
    it->first->Close();

  m_transfers.clear();

  libusb_close(m_handle);
  m_handle = nullptr;
}

void CUSBDeviceHandle::BeforeSubmit(CUSBTransfer* transfer)
{
  m_inflightTransfers.insert(transfer);
}

void CUSBDeviceHandle::AfterCompletion(CUSBTransfer* transfer)
{
  auto it1 = m_inflightTransfers.find(transfer);
  if (it1 != m_inflightTransfers.end())
    m_inflightTransfers.erase(it1);

  for (auto it2 = m_transfers.begin(); it2 != m_transfers.end(); ++it2)
  {
    if (it2->first.get() == transfer)
    {
      m_transfers.erase(it2);
      break;
    }
  }
}

void CUSBDeviceHandle::OnTransferComplete(CUSBTransfer* transfer)
{
  if (transfer->Status() != LIBUSB_TRANSFER_COMPLETED)
    return;

  for (auto it = m_transfers.begin(); it != m_transfers.end(); ++it)
  {
    if (it->first.get() == transfer)
    {
      it->second->OnTransferComplete(transfer->Buffer());
      break;
    }
  }

  transfer->Submit(); // TODO
}

bool CUSBDeviceHandle::ClaimInterface(unsigned int interfaceNumber)
{
  if (m_handle == nullptr)
  {
    esyslog("Cannot claim interface on closed handle");
    return false;
  }

  int res = libusb_claim_interface(m_handle, interfaceNumber);
  if (res < 0)
  {
    esyslog("Failed to claim interface");
    return false;
  }

  return true;
}

void CUSBDeviceHandle::ReleaseInterface(unsigned int interfaceNumber)
{
  if (m_handle == nullptr)
  {
    esyslog("Cannot release interface on closed handle");
    return;
  }

  int res = libusb_release_interface(m_handle, interfaceNumber);
  if (res < 0)
    esyslog("Failed to release interface");
}

bool CUSBDeviceHandle::IsKernelDriverActive(unsigned int interfaceNumber)
{
  if (m_handle == nullptr)
    return false;

  return libusb_kernel_driver_active(m_handle, interfaceNumber) == 1;
}

bool CUSBDeviceHandle::DetachKernelDriver(unsigned int interfaceNumber)
{
  if (m_handle == nullptr)
  {
    esyslog("Cannot detach kernel driver from closed handle");
    return false;
  }

  int res = libusb_detach_kernel_driver(m_handle, interfaceNumber);
  if (res < 0)
  {
    esyslog("Failed to detach kernel driver");
    return false;
  }

  return true;
}

void CUSBDeviceHandle::InitializeTransfer(IMessageCallback* callback, uint8_t endpoint, unsigned int isoPackets /* = 0 */)
{
  if (m_handle == nullptr)
  {
    esyslog("Cannot initialize transfer on closed handle");
    return;
  }

  TransferPtr transfer = std::make_shared<CUSBTransfer>(m_handle, isoPackets, this);
  transfer->SetInterrupt(LIBUSB_ENDPOINT_IN | endpoint, 64, this);
  transfer->Submit();
  m_transfers.insert(std::make_pair(transfer, callback));
}

bool CUSBDeviceHandle::HasSubmittedTransfers()
{
  return !m_inflightTransfers.empty();
}

int CUSBDeviceHandle::ControlRead(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const std::vector<uint8_t>& data, unsigned int timeoutMs)
{
  // Read
  requestType = (requestType & ~LIBUSB_ENDPOINT_DIR_MASK) | LIBUSB_ENDPOINT_IN;

  return ControlTransfer(requestType, request, value, index, data, timeoutMs);
}

int CUSBDeviceHandle::ControlWrite(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const std::vector<uint8_t>& data, unsigned int timeoutMs)
{
  // Write
  requestType = (requestType & ~LIBUSB_ENDPOINT_DIR_MASK) | LIBUSB_ENDPOINT_OUT;

  return ControlTransfer(requestType, request, value, index, data, timeoutMs);
}

int CUSBDeviceHandle::ControlTransfer(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const std::vector<uint8_t>& data, unsigned int timeoutMs)
{
  if (m_handle == nullptr)
  {
    esyslog("Cannot perform transfer on closed handle");
    return -1;
  }

  return libusb_control_transfer(m_handle, requestType, request, value, index, const_cast<uint8_t*>(data.data()), data.size(), timeoutMs);
}
