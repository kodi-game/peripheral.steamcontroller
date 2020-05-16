/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "USBInterfaceSetting.h"

#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBInterfaceSetting::CUSBInterfaceSetting(const libusb_interface_descriptor& interDesc) :
  m_interDesc(interDesc)
{
}

uint8_t CUSBInterfaceSetting::Number() const
{
  return m_interDesc.bInterfaceNumber;
}

uint8_t CUSBInterfaceSetting::Class() const
{
  return m_interDesc.bInterfaceClass;
}

uint8_t CUSBInterfaceSetting::SubClass() const
{
  return m_interDesc.bInterfaceSubClass;
}

uint8_t CUSBInterfaceSetting::Protocol() const
{
  return m_interDesc.bInterfaceProtocol;
}
