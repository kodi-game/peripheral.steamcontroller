/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
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
