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

#pragma once

#include <kodi/addon-instance/Peripheral.h>

#include <memory>

class ATTRIBUTE_HIDDEN CPeripheralSteamController :
  public kodi::addon::CAddonBase,
  public kodi::addon::CInstancePeripheral
{
public:
  CPeripheralSteamController() { }
  virtual ~CPeripheralSteamController();

  virtual ADDON_STATUS Create() override;
  virtual ADDON_STATUS GetStatus() override;
  virtual ADDON_STATUS SetSetting(const std::string& settingName, const kodi::CSettingValue& settingValue) override;

  virtual void GetCapabilities(PERIPHERAL_CAPABILITIES &capabilities) override;
  virtual PERIPHERAL_ERROR PerformDeviceScan(unsigned int* peripheral_count, PERIPHERAL_INFO** scan_results) override;
  virtual void FreeScanResults(unsigned int peripheral_count, PERIPHERAL_INFO* scan_results) override;
  virtual PERIPHERAL_ERROR GetEvents(unsigned int* event_count, PERIPHERAL_EVENT** events) override;
  virtual void FreeEvents(unsigned int event_count, PERIPHERAL_EVENT* events) override;
  virtual bool SendEvent(const PERIPHERAL_EVENT* event) override;
  virtual PERIPHERAL_ERROR GetJoystickInfo(unsigned int index, JOYSTICK_INFO* info) override;
  virtual void FreeJoystickInfo(JOYSTICK_INFO* info) override;
  virtual PERIPHERAL_ERROR GetFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                                       unsigned int* feature_count, JOYSTICK_FEATURE** features) override;
  virtual void FreeFeatures(unsigned int feature_count, JOYSTICK_FEATURE* features) override;
  virtual PERIPHERAL_ERROR MapFeatures(const JOYSTICK_INFO* joystick, const char* controller_id,
                                       unsigned int feature_count, const JOYSTICK_FEATURE* features) override;
  virtual PERIPHERAL_ERROR GetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                                unsigned int* primitive_count,
                                                JOYSTICK_DRIVER_PRIMITIVE** primitives) override;
  virtual void FreePrimitives(unsigned int primitive_count, JOYSTICK_DRIVER_PRIMITIVE* primitives) override;
  virtual PERIPHERAL_ERROR SetIgnoredPrimitives(const JOYSTICK_INFO* joystick,
                                                unsigned int primitive_count,
                                                const JOYSTICK_DRIVER_PRIMITIVE* primitives) override;
  virtual void SaveButtonMap(const JOYSTICK_INFO* joystick) override;
  virtual void RevertButtonMap(const JOYSTICK_INFO* joystick) override;
  virtual void ResetButtonMap(const JOYSTICK_INFO* joystick, const char* controller_id) override;
  virtual void PowerOffJoystick(unsigned int index) override;
};
