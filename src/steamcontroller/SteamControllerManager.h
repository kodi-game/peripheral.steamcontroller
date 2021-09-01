/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "SteamControllerTypes.h"
#include "usb/USBTypes.h"

#include <memory>

namespace kodi
{
namespace addon
{
  class PeripheralEvent;
}
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

    void GetEvents(std::vector<kodi::addon::PeripheralEvent>& events);

    bool SendEvent(const kodi::addon::PeripheralEvent& events);

  private:
    ControllerVector m_controllers;
    std::unique_ptr<CUSBContext> m_context;

    static unsigned int m_nextControllerIndex;
  };
}
