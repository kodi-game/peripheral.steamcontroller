/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "SteamControllerManager.h"
#include "SteamController.h"
#include "usb/USBContext.h"
#include "usb/USBDevice.h"

#include <kodi/addon-instance/PeripheralUtils.h>

#include <algorithm>
#include <cstring>

using namespace STEAMCONTROLLER;

unsigned int CSteamControllerManager::m_nextControllerIndex = 0;

CSteamControllerManager::CSteamControllerManager() :
  m_context(new CUSBContext)
{
}

CSteamControllerManager& CSteamControllerManager::Get()
{
  static CSteamControllerManager instance;
  return instance;
}

bool CSteamControllerManager::Initialize()
{
  if (!m_context->Initialize())
    return false;

  return true;
}

void CSteamControllerManager::Deinitialize()
{
  m_controllers.clear();
  m_context->Deinitialize();
}

void CSteamControllerManager::GetControllers(ControllerVector& controllers)
{
  USB_ID wirelessId = { STEAM_CONTROLLER_VID, STEAM_CONTROLLER_PID_WIRELESS };
  USB_ID wiredId = { STEAM_CONTROLLER_VID, STEAM_CONTROLLER_PID_WIRED };

  DeviceVector devices;
  m_context->GetDevicesByID({ wirelessId, wiredId }, devices);

  for (auto& device : devices)
  {
    // TODO: Need a better uniqueness test
    if (!GetController(device))
    {
      ControllerPtr controller(std::make_shared<CSteamController>(device, m_nextControllerIndex++, m_context->GetFeedbackCallback()));
      if (controller->Initialize())
      {
        // Disable haptic auto feedback
        m_context->HandleEvents();
        controller->SendControl({ 0x81000000 });
        m_context->HandleEvents();
        controller->SendControl({ 0x87153284, 0x03180000, 0x31020008, 0x07000707, 0x00300000, 0x2f010000 });
        m_context->HandleEvents();

        m_controllers.emplace_back(std::move(controller));
      }
    }
  }

  // TODO: Handle removed devices

  controllers = m_controllers;
}

ControllerPtr CSteamControllerManager::GetController(unsigned int index)
{
  ControllerPtr controller;

  auto it = std::find_if(m_controllers.begin(), m_controllers.end(),
    [index](const ControllerPtr& controller)
    {
      return controller->Index() == index;
    });

  if (it != m_controllers.end())
    controller = *it;

  return controller;
}

ControllerPtr CSteamControllerManager::GetController(const DevicePtr& device)
{
  ControllerPtr controller;

  auto it = std::find_if(m_controllers.begin(), m_controllers.end(),
    [&device](const ControllerPtr& controller)
    {
      return controller->Device().VendorID() == device->VendorID() &&
             controller->Device().ProductID() == device->ProductID();
    });

  if (it != m_controllers.end())
    controller = *it;

  return controller;
}

void CSteamControllerManager::GetEvents(std::vector<kodi::addon::PeripheralEvent>& events)
{
  // TODO
}

bool CSteamControllerManager::SendEvent(const kodi::addon::PeripheralEvent& events)
{
  return false; // TODO
}
