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

#include "SteamControllerTypes.h"
#include "usb/USBTypes.h"

#include <memory>

namespace ADDON
{
  class PeripheralEvent;
}

namespace STEAMCONTROLLER
{
  class CUSBContext;

  class CSteamControllerManager
  {
    CSteamControllerManager();

  public:
    static CSteamControllerManager& Get();

    bool Initialize();
    void Deinitialize();

    void GetControllers(ControllerVector& controllers);

    ControllerPtr GetController(unsigned int index);

    ControllerPtr GetController(const DevicePtr& device);

    void GetEvents(std::vector<ADDON::PeripheralEvent>& events);

    bool SendEvent(const ADDON::PeripheralEvent& events);

  private:
    ControllerVector m_controllers;
    std::unique_ptr<CUSBContext> m_context;

    static unsigned int m_nextControllerIndex;
  };
}
