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
