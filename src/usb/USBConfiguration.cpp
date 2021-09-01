/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
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
