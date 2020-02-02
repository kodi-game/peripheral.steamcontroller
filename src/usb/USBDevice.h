/*
 *      Copyright (C) 2016-2020 Garrett Brown
 *      Copyright (C) 2016-2020 Team Kodi
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

#include "USBTypes.h"

struct libusb_device;
struct libusb_device_descriptor;

namespace STEAMCONTROLLER
{
  class CUSBConfiguration;
  class CUSBContext;

  /*!
   * \brief Represents a USB device
   */
  class CUSBDevice
  {
  public:
    CUSBDevice(libusb_device* device, CUSBContext& context);

    ~CUSBDevice();

    bool LoadDescriptor();

    uint16_t VendorID() const;
    uint16_t ProductID() const;

    bool LoadConfiguration();

    const CUSBConfiguration& GetConfiguration() { return *m_configuration; }

    DeviceHandlePtr Open();
    void Close();

  private:
    // Construction params
    CUSBContext& m_context;
    libusb_device* const m_device;

    std::unique_ptr<libusb_device_descriptor> m_descriptor;
    std::unique_ptr<CUSBConfiguration>        m_configuration;
  };
}
