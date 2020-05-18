/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "USBDevice.h"
#include "USBConfiguration.h"
#include "USBContext.h"
#include "USBDeviceHandle.h"
#include "util/Log.h"

#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBDevice::CUSBDevice(libusb_device* device, CUSBContext& context) :
  m_context(context),
  m_device(device),
  m_descriptor(new libusb_device_descriptor)
{
  libusb_ref_device(m_device);
}

CUSBDevice::~CUSBDevice()
{
  libusb_unref_device(m_device);
}

bool CUSBDevice::LoadDescriptor()
{
  int res = libusb_get_device_descriptor(m_device, m_descriptor.get());
  if (res < 0)
  {
    esyslog("Failed to get device descriptor (error = %d)", res);
    return false;
  }

  return true;
}

uint16_t CUSBDevice::VendorID() const
{
  return m_descriptor->idVendor;
}

uint16_t CUSBDevice::ProductID() const
{
  return m_descriptor->idProduct;
}

bool CUSBDevice::LoadConfiguration()
{
  // We only care about configuration 0
  const unsigned int configurationNumber = 0;

  libusb_config_descriptor* config = nullptr;
  int res = libusb_get_config_descriptor(m_device, 0, &config);
  if (res == LIBUSB_ERROR_NOT_FOUND)
  {
    // Some devices (ex windows' root hubs) tell they have one configuration,
    // but they have no configuration descriptor
    // REF: python-libusb1
    return false;
  }
  else if (res < 0)
  {
    esyslog("Failed to get config descriptor (error = %d)", res);
    return false;
  }

  m_configuration.reset(new CUSBConfiguration(config));

  return true;
}

DeviceHandlePtr CUSBDevice::Open()
{
  DeviceHandlePtr deviceHandle;

  libusb_device_handle* handle;
  int res = libusb_open(m_device, &handle);
  if (res < 0)
  {
    esyslog("Failed to open device (error = %d)", res);
  }
  else
  {
    deviceHandle.reset(new CUSBDeviceHandle(handle, m_context));
  }

  return deviceHandle;
}
