/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "USBTypes.h"

#include <vector>

struct libusb_context;

namespace STEAMCONTROLLER
{
  class CUSBThread;
  class IFeedbackCallback;

  /*!
   * \brief libusb1 USB context
   *
   * This class provides methods to enumerate and look up USB devices. It also
   * provides access to global (device-independent) libusb1 functions (TODO).
   */
  class CUSBContext
  {
  public:
    CUSBContext();

    ~CUSBContext();

    bool Initialize();
    void Deinitialize();

    void GetDevicesByID(const std::vector<USB_ID>& ids, DeviceVector& result);

    /*!
     * \brief Handle any pending event in blocking mode
     *
     * See libusb1 documentation for details (there is a timeout, so it's
     * not "really" blocking).
     */
    void HandleEvents();

    IFeedbackCallback* GetFeedbackCallback();

  private:
    libusb_context* m_context;
    std::unique_ptr<CUSBThread> m_thread;
  };
}
