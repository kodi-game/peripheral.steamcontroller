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

#include "USBThread.h"
#include "USBContext.h"
#include "USBDeviceHandle.h"
#include "USBTransfer.h"
#include "usb/interfaces/ISendMessageCallback.h"

#include <kodi/addon-instance/PeripheralUtils.h>

#include <algorithm>
#include <assert.h>
#include <chrono>
#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBThread::CUSBThread(CUSBContext* context) :
  m_context(context)
{
  assert(m_context != nullptr);
}

CUSBThread::~CUSBThread()
{
  Deinitialize();
}

void CUSBThread::Deinitialize()
{
  m_isStopped = true;
  if (m_thread->joinable())
    m_thread->join();

  delete m_thread;
  m_thread = nullptr;
}

void CUSBThread::RegisterDeviceHandle(CUSBDeviceHandle* deviceHandle)
{
  std::unique_lock<std::mutex> lock(m_mutex);

  m_deviceHandles.push_back(deviceHandle);

  m_isStopped = false;
  m_thread = new std::thread(&CUSBThread::Process, this);
}

void CUSBThread::UnregisterDeviceHandle(CUSBDeviceHandle* deviceHandle)
{
  std::unique_lock<std::mutex> lock(m_mutex);

  m_deviceHandles.erase(std::remove(m_deviceHandles.begin(), m_deviceHandles.end(), deviceHandle), m_deviceHandles.end());

  if (m_deviceHandles.empty())
  {
    lock.unlock();
    Deinitialize();
  }
}

void CUSBThread::AddMessage(ISendMessageCallback* callback, std::vector<uint8_t>&& message)
{
  std::unique_lock<std::mutex> lock(m_mutex);

  m_messagesIn.push_front({ callback, message });
}

void CUSBThread::SendMessage(const FeedbackMessage& message)
{
  message.callback->SendControl(message.data.data(), message.data.size());
}

void CUSBThread::Process()
{
  while (!m_isStopped)
  {
    bool bIsAnySubmitted = true; // TODO

    {
      std::unique_lock<std::mutex> lock(m_mutex);

      // Check if any device handles have transfers submitted
      auto itDeviceHandle = std::find_if(m_deviceHandles.begin(), m_deviceHandles.end(),
        [](CUSBDeviceHandle* deviceHandle)
        {
          return deviceHandle->HasSubmittedTransfers();
        });

      bIsAnySubmitted = (itDeviceHandle != m_deviceHandles.end());
    }

    if (bIsAnySubmitted)
    {
      m_context->HandleEvents();

      std::unique_lock<std::mutex> lock(m_mutex);

      // Handle haptic feedback
      if (!m_messagesIn.empty())
      {
        SendMessage(m_messagesIn.back());
        m_messagesIn.pop_back();
      }
    }
    else
      std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
}
