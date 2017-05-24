/*
 *      Copyright (C) 2015-2016 Garrett Brown
 *      Copyright (C) 2015-2016 Team Kodi
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

/*
 * Derived from __init__.py of the Standalone Steam Controller Driver by ynsta
 *
 *
 * Copyright (c) 2015 Stany MARCEL <stanypub@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Also derived from usb1.py of the python-libusb1 project
 *
 *
 * Copyright (C) 2010-2016  Vincent Pelletier <plr.vincent@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "steamcontroller/SteamController.h"
#include "steamcontroller/SteamControllerManager.h"
#include "util/Log.h"

#define PERIPHERAL_ADDON_JOYSTICKS

#include "xbmc_addon_dll.h"
#include "kodi_peripheral_dll.h"
#include "kodi_peripheral_utils.hpp"
#include "libXBMC_addon.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

namespace STEAMCONTROLLER
{
  std::unique_ptr<ADDON::CHelper_libXBMC_addon> FRONTEND;
}

using namespace STEAMCONTROLLER;

extern "C"
{

ADDON_STATUS ADDON_Create(void* callbacks, void* props)
{
  if (callbacks != nullptr)
  {
    std::unique_ptr<ADDON::CHelper_libXBMC_addon> frontend(new ADDON::CHelper_libXBMC_addon);
    if (!frontend->RegisterMe(callbacks))
      return ADDON_STATUS_PERMANENT_FAILURE;

    // Initialize log here because other components depend on it
    CLog::Get().Initailize(frontend.get());

    //! @TODO Fix hang in USB thread
#if 0
    if (!CSteamControllerManager::Get().Initialize())
    {
      CLog::Get().Deinitailize();
      return ADDON_STATUS_PERMANENT_FAILURE;
    }
#endif

    // Success
    FRONTEND = std::move(frontend);
  }

  return ADDON_GetStatus();
}

void ADDON_Destroy()
{
  CSteamControllerManager::Get().Deinitialize();

  CLog::Get().Deinitailize();

  FRONTEND.reset();
}

ADDON_STATUS ADDON_GetStatus()
{
  if (FRONTEND == nullptr)
    return ADDON_STATUS_UNKNOWN;

  return ADDON_STATUS_OK;
}

ADDON_STATUS ADDON_SetSetting(const char* settingName, const void* settingValue)
{
  return ADDON_STATUS_OK;
}

PERIPHERAL_ERROR GetAddonCapabilities(PERIPHERAL_CAPABILITIES* pCapabilities)
{
  if (pCapabilities == nullptr)
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
  if (peripheral_count == nullptr || scan_results == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  ControllerVector controllers;

  //! @todo Fix permission error when opening usb device
#if 0
  CSteamControllerManager::Get().GetControllers(controllers);
#endif

  std::vector<ADDON::Peripheral> peripherals;
  std::transform(controllers.begin(), controllers.end(), std::back_inserter(peripherals),
    [](const ControllerPtr& controller)
    {
      ADDON::Peripheral peripheralInfo;
      controller->GetPeripheralInfo(peripheralInfo);
      return peripheralInfo;
    });

  *peripheral_count = peripherals.size();
  ADDON::Peripherals::ToStructs(peripherals, scan_results);

  return PERIPHERAL_NO_ERROR;
}

void FreeScanResults(unsigned int peripheral_count, PERIPHERAL_INFO* scan_results)
{
  ADDON::Peripherals::FreeStructs(peripheral_count, scan_results);
}

PERIPHERAL_ERROR GetEvents(unsigned int* event_count, PERIPHERAL_EVENT** events)
{
  if (event_count == nullptr || events == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  std::vector<ADDON::PeripheralEvent> peripheralEvents;

  //! @todo Fix bug causing infinite loop
#if 0
  CSteamControllerManager::Get().GetEvents(peripheralEvents);
#endif

  *event_count = peripheralEvents.size();
  ADDON::PeripheralEvents::ToStructs(peripheralEvents, events);

  return PERIPHERAL_NO_ERROR;
}

void FreeEvents(unsigned int event_count, PERIPHERAL_EVENT* events)
{
  ADDON::PeripheralEvents::FreeStructs(event_count, events);
}

bool SendEvent(const PERIPHERAL_EVENT* event)
{
  if (event == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  ADDON::PeripheralEvent peripheralEvent(*event);

  return CSteamControllerManager::Get().SendEvent(peripheralEvent);
}

PERIPHERAL_ERROR GetJoystickInfo(unsigned int index, JOYSTICK_INFO* info)
{
  if (info == nullptr)
    return PERIPHERAL_ERROR_INVALID_PARAMETERS;

  ControllerPtr controller = CSteamControllerManager::Get().GetController(index);
  if (controller)
  {
    ADDON::Joystick joystickInfo;
    controller->GetJoystickInfo(joystickInfo);
    joystickInfo.ToStruct(*info);
    return PERIPHERAL_NO_ERROR;
  }

  return PERIPHERAL_ERROR_FAILED;
}

void FreeJoystickInfo(JOYSTICK_INFO* info)
{
  if (info == nullptr)
    return;

  ADDON::Joystick::FreeStruct(*info);
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
                             unsigned int feature_count, const JOYSTICK_FEATURE* features)
{
  return PERIPHERAL_ERROR_FAILED;
}

PERIPHERAL_ERROR GetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                      unsigned int* primitive_count,
                                      JOYSTICK_DRIVER_PRIMITIVE** primitives)
{
  return PERIPHERAL_ERROR_FAILED;
}

void FreePrimitives(unsigned int primitive_count, JOYSTICK_DRIVER_PRIMITIVE* primitives)
{
}

PERIPHERAL_ERROR SetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                      unsigned int primitive_count,
                                      const JOYSTICK_DRIVER_PRIMITIVE* primitives)
{
  return PERIPHERAL_ERROR_FAILED;
}

void SaveButtonMap(const JOYSTICK_INFO* joystick)
{
}

void RevertButtonMap(const JOYSTICK_INFO* joystick)
{
}

void ResetButtonMap(const JOYSTICK_INFO* joystick, const char* controller_id)
{
}

void PowerOffJoystick(unsigned int index)
{
}

} // extern "C"
