/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <stdint.h>

struct libusb_interface_descriptor;

namespace STEAMCONTROLLER
{
  class CUSBInterfaceSetting
  {
  public:
    CUSBInterfaceSetting(const libusb_interface_descriptor& interDesc);

    uint8_t Number() const;
    uint8_t Class() const;
    uint8_t SubClass() const;
    uint8_t Protocol() const;

  private:
    const libusb_interface_descriptor& m_interDesc;
  };
}
