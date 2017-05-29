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
