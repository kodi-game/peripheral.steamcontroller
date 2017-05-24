/*
 *      Copyright (C) 2015 Garrett Brown
 *      Copyright (C) 2015 Team XBMC
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#define PERIPHERAL_ADDON_JOYSTICKS

#include "xbmc_addon_dll.h"
#include "kodi_peripheral_dll.h"

extern "C"
{

ADDON_STATUS ADDON_Create(void* callbacks, void* props)
{
  return ADDON_GetStatus();
}

void ADDON_Stop()
{
}

void ADDON_Destroy()
{
}

ADDON_STATUS ADDON_GetStatus()
{
  return ADDON_STATUS_UNKNOWN;
}

bool ADDON_HasSettings()
{
  return false;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting*** sSet)
{
  return 0;
}

ADDON_STATUS ADDON_SetSetting(const char* settingName, const void* settingValue)
{
  return ADDON_STATUS_OK;
}

void ADDON_FreeSettings()
{
}

void ADDON_Announce(const char* flag, const char* sender, const char* message, const void* data)
{
}

const char* GetPeripheralAPIVersion(void)
{
  return PERIPHERAL_API_VERSION;
}

const char* GetMinimumPeripheralAPIVersion(void)
{
  return PERIPHERAL_MIN_API_VERSION;
}

PERIPHERAL_ERROR GetAddonCapabilities(PERIPHERAL_CAPABILITIES* pCapabilities)
{
  if (!pCapabilities)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  pCapabilities->provides_joysticks = true;

  return PERIPHERAL_NO_ERROR;
}

bool SupportsDevice(const char* device_name)
{
  return false;
}

PERIPHERAL_ERROR PerformDeviceScan(unsigned int* peripheral_count, PERIPHERAL_INFO** scan_results)
{
  return PERIPHERAL_ERROR_FAILED;
}

void FreeScanResults(unsigned int peripheral_count, PERIPHERAL_INFO* scan_results)
{
}

PERIPHERAL_ERROR GetEvents(unsigned int* event_count, PERIPHERAL_EVENT** events)
{
  return PERIPHERAL_ERROR_FAILED;
}

void FreeEvents(unsigned int event_count, PERIPHERAL_EVENT* events)
{
}

bool SendEvent(const PERIPHERAL_EVENT* event)
{
  return false;
}

PERIPHERAL_ERROR GetJoystickInfo(unsigned int index, JOYSTICK_INFO* info)
{
  return PERIPHERAL_ERROR_FAILED;
}

void FreeJoystickInfo(JOYSTICK_INFO* info)
{
}

PERIPHERAL_ERROR GetFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                             unsigned int* feature_count, JOYSTICK_FEATURE** features)
{
  return PERIPHERAL_ERROR_FAILED;
}

void FreeFeatures(unsigned int feature_count, JOYSTICK_FEATURE* features)
{
}

PERIPHERAL_ERROR MapFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                             unsigned int feature_count, JOYSTICK_FEATURE* features)
{
  return PERIPHERAL_ERROR_FAILED;
}

void SaveButtonMap(const JOYSTICK_INFO* joystick)
{
}

void ResetButtonMap(const JOYSTICK_INFO* joystick, const char* controller_id)
{
}

void PowerOffJoystick(unsigned int index)
{
}

} // extern "C"
