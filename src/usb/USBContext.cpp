/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "USBContext.h"
#include "USBDevice.h"
#include "USBThread.h"
#include "util/Log.h"

#include <kodi/addon-instance/PeripheralUtils.h>

#include <algorithm>
#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBContext::CUSBContext() :
  m_context(nullptr),
  m_thread(new CUSBThread(this))
{
}

CUSBContext::~CUSBContext()
{
  Deinitialize();
}

bool CUSBContext::Initialize()
{
  int res = libusb_init(&m_context);
  if (res < 0)
  {
    esyslog("Failed to initialize libusb (error = %d)", res);
    return false;
  }

  // Set verbosity level to 3, as suggested in the documentation
  libusb_set_debug(m_context, 3);

  m_thread->Initialize();

  return true;
}

void CUSBContext::Deinitialize()
{
  m_thread->Deinitialize();

  if (m_context)
  {
    libusb_exit(m_context);
    m_context = nullptr;
  }
}

void CUSBContext::GetDevicesByID(const std::vector<USB_ID>& ids, DeviceVector& result)
{
  if (m_context == nullptr)
    return;

  libusb_device** devices;
  ssize_t count = libusb_get_device_list(m_context, &devices);

  if (count < 0)
  {
    esyslog("Failed to get list of USB devices");
    return;
  }

  for (ssize_t i = 0; i < count; i++)
  {
    libusb_device* dev = devices[i];
    DevicePtr device = std::make_shared<CUSBDevice>(dev, *this);

    if (device->LoadDescriptor())
    {
      USB_ID deviceId = { device->VendorID(), device->ProductID() };

      // Check if device's USB ID appears in the list parameter
      auto it = std::find(ids.begin(), ids.end(), deviceId);

      if (it != ids.end())
      {
        if (device->LoadConfiguration())
          result.emplace_back(std::move(device));
      }
    }
  }

  libusb_free_device_list(devices, 1);
}

void CUSBContext::HandleEvents()
{
  if (m_context == nullptr)
    return;

  int res = libusb_handle_events(m_context);
  if (res < 0)
    esyslog("Failed to handle USB events (error = %d)", res);
}

IFeedbackCallback* CUSBContext::GetFeedbackCallback()
{
  return m_thread.get();
}
