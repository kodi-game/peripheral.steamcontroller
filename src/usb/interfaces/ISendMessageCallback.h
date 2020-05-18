/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <stdint.h>

namespace STEAMCONTROLLER
{
  class ISendMessageCallback
  {
  public:
    virtual ~ISendMessageCallback() = default;

    virtual void SendControl(const uint8_t* data, size_t length, unsigned int timeout = 0) = 0;
  };
}
