/*
 *  Copyright (C) 2015-2020 Garrett Brown
 *  Copyright (C) 2015-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "addon.h"
#include "steamcontroller/SteamController.h"
#include "steamcontroller/SteamControllerManager.h"
#include "util/Log.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

using namespace STEAMCONTROLLER;

ADDON_STATUS CPeripheralSteamController::Create()
{
  //! @TODO Fix hang in USB thread
#if 0
  if (!CSteamControllerManager::Get().Initialize())
  {
    CLog::Get().Deinitailize();
    return ADDON_STATUS_PERMANENT_FAILURE;
  }
#endif

  return GetStatus();
}

CPeripheralSteamController::~CPeripheralSteamController()
{
  CSteamControllerManager::Get().Deinitialize();
}

ADDON_STATUS CPeripheralSteamController::GetStatus()
{
  return ADDON_STATUS_OK;
}

ADDON_STATUS CPeripheralSteamController::SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue)
{
  return ADDON_STATUS_OK;
}

void CPeripheralSteamController::GetCapabilities(kodi::addon::PeripheralCapabilities& capabilities)
{
  capabilities.SetProvidesJoysticks(true);
}

bool SupportsDevice(const char* device_name)
{
  return false;
}

PERIPHERAL_ERROR CPeripheralSteamController::PerformDeviceScan(std::vector<std::shared_ptr<kodi::addon::Peripheral>>& scan_results)
{
  //! @todo Fix permission error when opening usb device
#if 0
  CSteamControllerManager::Get().GetControllers(scan_results);
#endif

  return PERIPHERAL_NO_ERROR;
}

PERIPHERAL_ERROR CPeripheralSteamController::GetEvents(std::vector<kodi::addon::PeripheralEvent>& events)
{
  //! @todo Fix bug causing infinite loop
#if 0
  CSteamControllerManager::Get().GetEvents(events);
#endif

  return PERIPHERAL_NO_ERROR;
}

bool CPeripheralSteamController::SendEvent(const kodi::addon::PeripheralEvent& event)
{
  return CSteamControllerManager::Get().SendEvent(event);
}

PERIPHERAL_ERROR CPeripheralSteamController::GetJoystickInfo(unsigned int index, kodi::addon::Joystick& info)
{
  ControllerPtr controller = CSteamControllerManager::Get().GetController(index);
  if (controller)
  {
    controller->GetJoystickInfo(info);
    return PERIPHERAL_NO_ERROR;
  }

  return PERIPHERAL_ERROR_FAILED;
}

PERIPHERAL_ERROR CPeripheralSteamController::GetFeatures(const kodi::addon::Joystick& joystick,
                                                         const std::string& controller_id,
                                                         std::vector<kodi::addon::JoystickFeature>& features)
{
  return PERIPHERAL_ERROR_FAILED;
}

PERIPHERAL_ERROR CPeripheralSteamController::MapFeatures(const kodi::addon::Joystick& joystick,
                                                         const std::string& controller_id,
                                                         const std::vector<kodi::addon::JoystickFeature>& features)
{
  return PERIPHERAL_ERROR_FAILED;
}

PERIPHERAL_ERROR CPeripheralSteamController::GetIgnoredPrimitives(const kodi::addon::Joystick& joystick,
                                                                  std::vector<kodi::addon::DriverPrimitive>& primitives)
{
  return PERIPHERAL_ERROR_FAILED;
}

PERIPHERAL_ERROR CPeripheralSteamController::SetIgnoredPrimitives(const kodi::addon::Joystick& joystick,
                                                                  const std::vector<kodi::addon::DriverPrimitive>& primitives)
{
  return PERIPHERAL_ERROR_FAILED;
}

void CPeripheralSteamController::SaveButtonMap(const kodi::addon::Joystick& joystick)
{

}

void CPeripheralSteamController::RevertButtonMap(const kodi::addon::Joystick& joystick)
{

}

void CPeripheralSteamController::ResetButtonMap(const kodi::addon::Joystick& joystick, const std::string& controller_id)
{

}

void CPeripheralSteamController::PowerOffJoystick(unsigned int index)
{
}

ADDONCREATOR(CPeripheralSteamController) // Don't touch this!
