/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "USBInterfaceSetting.h"

struct libusb_interface;

namespace STEAMCONTROLLER
{
  class CUSBInterface
  {
  public:
    CUSBInterface(const libusb_interface& interface);

    unsigned int SettingCount() const;

    CUSBInterfaceSetting GetSetting(unsigned int settingNumber);

  private:
    const libusb_interface& m_interface;
  };
}
