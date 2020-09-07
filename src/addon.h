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

  void GetCapabilities(kodi::addon::PeripheralCapabilities& capabilities) override;
  PERIPHERAL_ERROR PerformDeviceScan(std::vector<std::shared_ptr<kodi::addon::Peripheral>>& scan_results) override;
  PERIPHERAL_ERROR GetEvents(std::vector<kodi::addon::PeripheralEvent>& events) override;
  bool SendEvent(const kodi::addon::PeripheralEvent& event) override;
  PERIPHERAL_ERROR GetJoystickInfo(unsigned int index, kodi::addon::Joystick& info) override;
  PERIPHERAL_ERROR GetFeatures(const kodi::addon::Joystick& joystick,
                               const std::string& controller_id,
                               std::vector<kodi::addon::JoystickFeature>& features) override;
  PERIPHERAL_ERROR MapFeatures(const kodi::addon::Joystick& joystick,
                               const std::string& controller_id,
                               const std::vector<kodi::addon::JoystickFeature>& features) override;
  PERIPHERAL_ERROR GetIgnoredPrimitives(const kodi::addon::Joystick& joystick,
                                        std::vector<kodi::addon::DriverPrimitive>& primitives) override;
  PERIPHERAL_ERROR SetIgnoredPrimitives(const kodi::addon::Joystick& joystick,
                                        const std::vector<kodi::addon::DriverPrimitive>& primitives) override;
  void SaveButtonMap(const kodi::addon::Joystick& joystick) override;
  void RevertButtonMap(const kodi::addon::Joystick& joystick) override;
  void ResetButtonMap(const kodi::addon::Joystick& joystick, const std::string& controller_id) override;
  void PowerOffJoystick(unsigned int index) override;
};
