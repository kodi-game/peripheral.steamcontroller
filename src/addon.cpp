/*
 *      Copyright (C) 2015-2020 Garrett Brown
 *      Copyright (C) 2015-2020 Team Kodi
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

#include "addon.h"
#include "steamcontroller/SteamController.h"
#include "steamcontroller/SteamControllerManager.h"
#include "util/Log.h"

#include <kodi/addon-instance/PeripheralUtils.h>

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

void CPeripheralSteamController::GetCapabilities(PERIPHERAL_CAPABILITIES& capabilities)
{
  capabilities.provides_joysticks = true;
}

bool SupportsDevice(const char* device_name)
{
  return false;
}

PERIPHERAL_ERROR CPeripheralSteamController::PerformDeviceScan(unsigned int* peripheral_count, PERIPHERAL_INFO** scan_results)
{
  if (peripheral_count == nullptr || scan_results == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  ControllerVector controllers;

  //! @todo Fix permission error when opening usb device
#if 0
  CSteamControllerManager::Get().GetControllers(controllers);
#endif

  std::vector<kodi::addon::Peripheral> peripherals;
  std::transform(controllers.begin(), controllers.end(), std::back_inserter(peripherals),
    [](const ControllerPtr& controller)
    {
      kodi::addon::Peripheral peripheralInfo;
      controller->GetPeripheralInfo(peripheralInfo);
      return peripheralInfo;
    });

  *peripheral_count = peripherals.size();
  kodi::addon::Peripherals::ToStructs(peripherals, scan_results);

  return PERIPHERAL_NO_ERROR;
}

void CPeripheralSteamController::FreeScanResults(unsigned int peripheral_count, PERIPHERAL_INFO* scan_results)
{
  kodi::addon::Peripherals::FreeStructs(peripheral_count, scan_results);
}

PERIPHERAL_ERROR CPeripheralSteamController::GetEvents(unsigned int* event_count, PERIPHERAL_EVENT** events)
{
  if (event_count == nullptr || events == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  std::vector<kodi::addon::PeripheralEvent> peripheralEvents;

  //! @todo Fix bug causing infinite loop
#if 0
  CSteamControllerManager::Get().GetEvents(peripheralEvents);
#endif

  *event_count = peripheralEvents.size();
  kodi::addon::PeripheralEvents::ToStructs(peripheralEvents, events);

  return PERIPHERAL_NO_ERROR;
}

void CPeripheralSteamController::FreeEvents(unsigned int event_count, PERIPHERAL_EVENT* events)
{
  kodi::addon::PeripheralEvents::FreeStructs(event_count, events);
}

bool CPeripheralSteamController::SendEvent(const PERIPHERAL_EVENT* event)
{
  if (event == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  kodi::addon::PeripheralEvent peripheralEvent(*event);

  return CSteamControllerManager::Get().SendEvent(peripheralEvent);
}

PERIPHERAL_ERROR CPeripheralSteamController::GetJoystickInfo(unsigned int index, JOYSTICK_INFO* info)
{
  if (info == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  ControllerPtr controller = CSteamControllerManager::Get().GetController(index);
  if (controller)
  {
    kodi::addon::Joystick joystickInfo;
    controller->GetJoystickInfo(joystickInfo);
    joystickInfo.ToStruct(*info);
    return PERIPHERAL_NO_ERROR;
  }

  return PERIPHERAL_ERROR_FAILED;
}

void CPeripheralSteamController::FreeJoystickInfo(JOYSTICK_INFO* info)
{
  if (info == nullptr)
    return;

  kodi::addon::Joystick::FreeStruct(*info);
}

PERIPHERAL_ERROR CPeripheralSteamController::GetFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                                                         unsigned int* feature_count, JOYSTICK_FEATURE** features)
{
  return PERIPHERAL_ERROR_FAILED;
}

void CPeripheralSteamController::FreeFeatures(unsigned int feature_count, JOYSTICK_FEATURE* features)
{
}

PERIPHERAL_ERROR CPeripheralSteamController::MapFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                                                         unsigned int feature_count, const JOYSTICK_FEATURE* features)
{
  return PERIPHERAL_ERROR_FAILED;
}

PERIPHERAL_ERROR CPeripheralSteamController::GetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                                                  unsigned int* primitive_count,
                                                                  JOYSTICK_DRIVER_PRIMITIVE** primitives)
{
  return PERIPHERAL_ERROR_FAILED;
}

void CPeripheralSteamController::FreePrimitives(unsigned int primitive_count, JOYSTICK_DRIVER_PRIMITIVE* primitives)
{
}

PERIPHERAL_ERROR CPeripheralSteamController::SetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                                                  unsigned int primitive_count,
                                                                  const JOYSTICK_DRIVER_PRIMITIVE* primitives)
{
  return PERIPHERAL_ERROR_FAILED;
}

void CPeripheralSteamController::SaveButtonMap(const JOYSTICK_INFO* joystick)
{
}

void CPeripheralSteamController::RevertButtonMap(const JOYSTICK_INFO* joystick)
{
}

void CPeripheralSteamController::ResetButtonMap(const JOYSTICK_INFO* joystick, const char* controller_id)
{
}

void CPeripheralSteamController::PowerOffJoystick(unsigned int index)
{
}

ADDONCREATOR(CPeripheralSteamController) // Don't touch this!
