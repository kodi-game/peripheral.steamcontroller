/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "USBTransfer.h"
#include "usb/interfaces/ITransferCallback.h"
#include "usb/interfaces/ITransferObserver.h"
#include "util/Log.h"

#include <assert.h>
#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBTransfer::CUSBTransfer(libusb_device_handle* handle, unsigned int isoPackets, ITransferObserver* observer) :
  m_handle(handle),
  m_observer(observer),
  m_bInitailized(false),
  m_bSubmitted(false),
  m_bDoomed(false),
  m_callback(nullptr),
  m_transfer(libusb_alloc_transfer(isoPackets))
{
  assert(m_handle != nullptr);
  assert(m_observer != nullptr);
}

CUSBTransfer::~CUSBTransfer()
{
  Cancel();
  libusb_free_transfer(m_transfer);
}

void CUSBTransfer::Close()
{
  if (m_bSubmitted)
  {
    esyslog("Can't close a submitted transfer");
    return;
  }

  Doom();

  m_bInitailized = false;
  m_callback = nullptr;
}

void CUSBTransfer::Doom()
{
  m_bDoomed = true;
}

bool CUSBTransfer::SetInterrupt(uint8_t endpoint, unsigned int bufferLength, ITransferCallback* callback, unsigned int timeoutMs /* = 0 */)
{
  std::string buffer;
  buffer.resize(bufferLength);
  return SetInterrupt(endpoint, buffer, callback, timeoutMs);
}

bool CUSBTransfer::SetInterrupt(uint8_t endpoint, const std::string& buffer, ITransferCallback* callback, unsigned int timeoutMs /* = 0 */)
{
  if (m_bSubmitted)
  {
    esyslog("Cannot alter a submitted transfer");
    return false;
  }

  if (m_bDoomed)
  {
    esyslog("Cannot reuse a doomed transfer");
    return false;
  }

  m_bInitailized = false;
  m_transferBuffer = buffer;
  m_callback = callback;

  // TODO
  uint8_t* data = reinterpret_cast<uint8_t*>(const_cast<char*>(buffer.c_str()));

  libusb_fill_interrupt_transfer(m_transfer, m_handle, endpoint, data, buffer.length(), transfer_cb_fn, this, timeoutMs);

  m_bInitailized = true;

  return true;
}

int CUSBTransfer::Status() const
{
  return static_cast<int>(m_transfer->status);
}

int CUSBTransfer::ActualLength() const
{
  return m_transfer->actual_length;
}

std::vector<uint8_t> CUSBTransfer::Buffer() const
{
  size_t offset = 0;

  if (static_cast<libusb_transfer_type>(m_transfer->type) == LIBUSB_TRANSFER_TYPE_CONTROL)
  {
    // Get the data section of a control transfer. The data does not start
    // until 8 bytes into the actual buffer, as the setup packet comes first.
    offset = libusb_control_transfer_get_data(m_transfer) - m_transfer->buffer;
  }

  std::vector<uint8_t> buffer(m_transfer->buffer + offset, m_transfer->buffer + m_transfer->length - offset);

  return buffer;
}

bool CUSBTransfer::IsSubmitted() const
{
  return m_bSubmitted;
}

bool CUSBTransfer::Submit()
{
  if (m_bSubmitted)
  {
    esyslog("Cannot submit a submitted transfer");
    return false;
  }

  if (!m_bInitailized)
  {
    esyslog("Cannot submit a transfer until it has been initialized");
    return false;
  }

  if (m_bDoomed)
  {
    esyslog("Cannot submit doomed transfer");
    return false;
  }

  m_observer->BeforeSubmit(this);
  m_bSubmitted = true;

  int res = libusb_submit_transfer(m_transfer);
  if (res < 0)
  {
    m_bSubmitted = false;
    m_observer->AfterCompletion(this);
    return false;
  }

  return true;
}

void CUSBTransfer::Cancel()
{
  if (!m_bSubmitted)
  {
    // XXX: Workaround for a bug reported on libusb 1.0.8: calling
    // libusb_cancel_transfer on a non-submitted transfer might
    // trigger a segfault.
    return;
  }

  int res = libusb_cancel_transfer(m_transfer);
  if (res < 0)
    esyslog("Failed to cancel submitted transfer (error = %d)", res);
}

void CUSBTransfer::TransferCallback(libusb_transfer* transfer)
{
  m_bSubmitted = false;
  m_observer->AfterCompletion(this);

  if (m_callback)
    m_callback->OnTransferComplete(this);

  if (m_bDoomed)
    Close();
}

void CUSBTransfer::transfer_cb_fn(libusb_transfer* transfer)
{
  if (transfer && transfer->user_data)
    static_cast<CUSBTransfer*>(transfer->user_data)->TransferCallback(transfer);
}
