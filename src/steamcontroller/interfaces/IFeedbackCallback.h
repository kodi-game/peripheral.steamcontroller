/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <stdint.h>
#include <vector>

namespace STEAMCONTROLLER
{
  class CUSBDeviceHandle;
  class ISendMessageCallback;

  class IFeedbackCallback
  {
  public:
    virtual ~IFeedbackCallback() = default;

    virtual void RegisterDeviceHandle(CUSBDeviceHandle* deviceHandle) = 0;
    virtual void UnregisterDeviceHandle(CUSBDeviceHandle* deviceHandle) = 0;
    virtual void AddMessage(ISendMessageCallback* callback, std::vector<uint8_t>&& message) = 0;
  };
}
