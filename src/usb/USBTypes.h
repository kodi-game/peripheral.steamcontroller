/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
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
