/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "USBInterface.h"

#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBInterface::CUSBInterface(const libusb_interface& interface) :
  m_interface(interface)
{
}

unsigned int CUSBInterface::SettingCount() const
{
  return m_interface.num_altsetting;
}

CUSBInterfaceSetting CUSBInterface::GetSetting(unsigned int settingNumber)
{
  const libusb_interface_descriptor& interDesc = m_interface.altsetting[settingNumber];
  return CUSBInterfaceSetting(interDesc);
}
