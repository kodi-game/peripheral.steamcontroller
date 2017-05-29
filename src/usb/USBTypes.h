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
#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

// Default string length
// From a comment in libusb-1.0: "Some devices choke on size > 255"
#define STRING_LENGTH  255

// As of v3 of USB specs, there cannot be more than 7 hubs from controller to device
#define PATH_MAX_DEPTH  7

namespace STEAMCONTROLLER
{
  class CUSBDevice;
  typedef std::shared_ptr<CUSBDevice> DevicePtr;
  typedef std::vector<DevicePtr>      DeviceVector;

  class CUSBDeviceHandle;
  typedef std::shared_ptr<CUSBDeviceHandle> DeviceHandlePtr;
  typedef std::vector<DeviceHandlePtr>      DeviceHandleVector;

  class CUSBTransfer;
  typedef std::shared_ptr<CUSBTransfer> TransferPtr;
  typedef std::vector<TransferPtr>      TransferVector;

  struct USB_ID
  {
    uint16_t vid;
    uint16_t pid;
  };

  inline bool operator==(const USB_ID& lhs, const USB_ID& rhs)
  {
    return lhs.vid == rhs.vid &&
           lhs.pid == rhs.pid;
  }
}
