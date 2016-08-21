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

#include "USBDevice.h"
#include "USBConfiguration.h"
#include "USBDeviceHandle.h"
#include "util/Log.h"

#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBDevice::CUSBDevice(libusb_device* device) :
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
  if (libusb_get_device_descriptor(m_device, m_descriptor.get()) < 0)
  {
    esyslog("Failed to get device descriptor");
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
    esyslog("Failed to get config descriptor");
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
    esyslog("Failed to open device");
  }
  else
  {
    deviceHandle.reset(new CUSBDeviceHandle(handle));
  }

  return deviceHandle;
}
