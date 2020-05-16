/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "USBInterface.h"

struct libusb_config_descriptor;

namespace STEAMCONTROLLER
{
  class CUSBConfiguration
  {
  public:
    CUSBConfiguration(libusb_config_descriptor* config);
    ~CUSBConfiguration();

    /*!
     * \brief Returns device's power consumption in mW
     *
     * Beware of unit: USB descriptor uses 2mW increments, this method converts
     * it to mW units.
     */
    unsigned int GetMaxPower() const;

    unsigned int InterfaceCount() const;

    CUSBInterface GetInterface(unsigned int interfaceNumber) const;

  private:
    // Construction params
    libusb_config_descriptor* const m_config;
  };
}
