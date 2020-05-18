/*
 *  Copyright (C) 2015-2020 Garrett Brown
 *  Copyright (C) 2015-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
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

#pragma once

#include <kodi/addon-instance/Peripheral.h>

#include <memory>

class ATTRIBUTE_HIDDEN CPeripheralSteamController :
  public kodi::addon::CAddonBase,
  public kodi::addon::CInstancePeripheral
{
public:
  CPeripheralSteamController() { }
  ~CPeripheralSteamController() override;

  ADDON_STATUS Create() override;
  ADDON_STATUS GetStatus() override;
  ADDON_STATUS SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue) override;

  void GetCapabilities(PERIPHERAL_CAPABILITIES &capabilities) override;
  PERIPHERAL_ERROR PerformDeviceScan(unsigned int* peripheral_count, PERIPHERAL_INFO** scan_results) override;
  void FreeScanResults(unsigned int peripheral_count, PERIPHERAL_INFO* scan_results) override;
  PERIPHERAL_ERROR GetEvents(unsigned int* event_count, PERIPHERAL_EVENT** events) override;
  void FreeEvents(unsigned int event_count, PERIPHERAL_EVENT* events) override;
  bool SendEvent(const PERIPHERAL_EVENT* event) override;
  PERIPHERAL_ERROR GetJoystickInfo(unsigned int index, JOYSTICK_INFO* info) override;
  void FreeJoystickInfo(JOYSTICK_INFO* info) override;
  PERIPHERAL_ERROR GetFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                               unsigned int* feature_count, JOYSTICK_FEATURE** features) override;
  void FreeFeatures(unsigned int feature_count, JOYSTICK_FEATURE* features) override;
  PERIPHERAL_ERROR MapFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                               unsigned int feature_count, const JOYSTICK_FEATURE* features) override;
  PERIPHERAL_ERROR GetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                        unsigned int* primitive_count,
                                        JOYSTICK_DRIVER_PRIMITIVE** primitives) override;
  void FreePrimitives(unsigned int primitive_count, JOYSTICK_DRIVER_PRIMITIVE* primitives) override;
  PERIPHERAL_ERROR SetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                        unsigned int primitive_count,
                                        const JOYSTICK_DRIVER_PRIMITIVE* primitives) override;
  void SaveButtonMap(const JOYSTICK_INFO* joystick) override;
  void RevertButtonMap(const JOYSTICK_INFO* joystick) override;
  void ResetButtonMap(const JOYSTICK_INFO* joystick, const char* controller_id) override;
  void PowerOffJoystick(unsigned int index) override;
};
