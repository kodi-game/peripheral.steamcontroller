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

#include "USBConfiguration.h"

#include <assert.h>
#include <libusb.h>

using namespace STEAMCONTROLLER;

CUSBConfiguration::CUSBConfiguration(libusb_config_descriptor* config) :
  m_config(config)
{
  assert(m_config != nullptr);
}

CUSBConfiguration::~CUSBConfiguration()
{
  libusb_free_config_descriptor(m_config);
}

unsigned int CUSBConfiguration::GetMaxPower() const
{
  return m_config->MaxPower * 2;
}

unsigned int CUSBConfiguration::InterfaceCount() const
{
  return m_config->bNumInterfaces;
}

CUSBInterface CUSBConfiguration::GetInterface(unsigned int interfaceNumber) const
{
  const libusb_interface& interface = m_config->interface[interfaceNumber];
  return CUSBInterface(interface);
}
