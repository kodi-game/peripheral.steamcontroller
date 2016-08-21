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
