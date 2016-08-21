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

#include "SteamController.h"
#include "SteamControllerInput.h"
#include "SteamControllerTranslator.h"
#include "SteamControllerTypes.h"
#include "steamcontroller/interfaces/IFeedbackCallback.h"
#include "usb/USBConfiguration.h"
#include "usb/USBDevice.h"
#include "usb/USBDeviceHandle.h"
#include "usb/USBInterface.h"
#include "usb/USBInterfaceSetting.h"
#include "usb/USBTransfer.h"

#include "kodi_peripheral_utils.hpp"
#include "p8-platform/util/timeutils.h"

#include <algorithm>
#include <assert.h>
#include <libusb.h>

using namespace STEAMCONTROLLER;

namespace STEAMCONTROLLER
{
  enum class Button
  {
    RPADTOUCH,
    LPADTOUCH,
    RPAD,
    LPAD,
    RGRIP,
    LGRIP,
    START,
    STEAM,
    BACK,
    A,
    X,
    B,
    Y,
    LB,
    RB,
    LT,
    RT,
  };

  struct ButtonMask
  {
    Button button;
    uint32_t mask;
  };

  std::vector<ButtonMask> buttonMap = {
    { Button::RPADTOUCH, 0b00010000000000000000000000000000 },
    { Button::LPADTOUCH, 0b00001000000000000000000000000000 },
    { Button::RPAD,      0b00000100000000000000000000000000 },
    { Button::LPAD,      0b00000010000000000000000000000000 }, // Same for stick but without LPadTouch
    { Button::RGRIP,     0b00000001000000000000000000000000 },
    { Button::LGRIP,     0b00000000100000000000000000000000 },
    { Button::START,     0b00000000010000000000000000000000 },
    { Button::STEAM,     0b00000000001000000000000000000000 },
    { Button::BACK,      0b00000000000100000000000000000000 },
    { Button::A,         0b00000000000000001000000000000000 },
    { Button::X,         0b00000000000000000100000000000000 },
    { Button::B,         0b00000000000000000010000000000000 },
    { Button::Y,         0b00000000000000000001000000000000 },
    { Button::LB,        0b00000000000000000000100000000000 },
    { Button::RB,        0b00000000000000000000010000000000 },
    { Button::LT,        0b00000000000000000000001000000000 },
    { Button::RT,        0b00000000000000000000000100000000 },
  };
}

CSteamController::CSteamController(const DevicePtr& device, unsigned int index, IFeedbackCallback* feedbackCallback) :
  m_device(device),
  m_index(index),
  m_feedbackCallback(feedbackCallback),
  m_input(new CSteamControllerInput),
  m_previousInput(new CSteamControllerInput),
  m_lastUsbTimeMs(-1),
  m_period(0.0f)
{
  assert(m_device.get() != nullptr);
  assert(m_feedbackCallback != nullptr);
}

CSteamController::~CSteamController()
{
  Deinitialize();
}

bool CSteamController::Initialize()
{
  m_deviceHandle = m_device->Open();

  if (!m_deviceHandle)
    return false;

  m_feedbackCallback->RegisterDeviceHandle(m_deviceHandle.get());

  ClaimInterfaces();

  m_deviceHandle->InitializeTransfer(this, GetEndpoint());

  m_period = STEAM_CONTROLLER_LPERIOD;

  if (m_device->ProductID() == STEAM_CONTROLLER_PID_WIRED)
  {
    // TODO: Timer
  }

  m_input->Reset();
  m_previousInput->Reset();

  m_lastUsbTimeMs = P8PLATFORM::GetTimeMs();

  return true;
}

void CSteamController::Deinitialize()
{
  m_feedbackCallback->UnregisterDeviceHandle(m_deviceHandle.get());
  m_deviceHandle.reset();
}

void CSteamController::OnTransferComplete(const std::vector<uint8_t>& message)
{
  if (!m_input->Deserialize(message))
    return;

  ProcessInput();
}

void CSteamController::ClaimInterfaces()
{
  const CUSBConfiguration& config = m_device->GetConfiguration();

  for (unsigned int i = 0; i < config.InterfaceCount(); i++)
  {
    CUSBInterface interface = config.GetInterface(i);

    for (unsigned int j = 0; j < interface.SettingCount(); j++)
    {
      CUSBInterfaceSetting setting = interface.GetSetting(j);
      uint8_t interfaceNumber = setting.Number();

      if (m_deviceHandle->IsKernelDriverActive(interfaceNumber))
      {
        if (!m_deviceHandle->DetachKernelDriver(interfaceNumber))
          continue;
      }

      if (setting.Class() == 3 &&
          setting.SubClass() == 0 &&
          setting.Protocol() == 0)
      {
        m_deviceHandle->ClaimInterface(interfaceNumber);
      }
    }
  }
}

void CSteamController::ProcessInput()
{
  if (m_input->Status() != InputStatus::INPUT)
    return;

  // TODO
  uint32_t xorButtons = m_input->Buttons() ^ m_previousInput->Buttons();
  uint32_t pressed = xorButtons & m_input->Buttons();
  uint32_t unpressed = xorButtons & m_previousInput->Buttons();

  for (auto& buttonMask : buttonMap)
  {
    if (buttonMask.mask & pressed)
    {
      // TODO: OnPress(buttonMask.button);
    }
    else if (buttonMask.mask & unpressed)
    {
      // TODO: OnUnpress(buttonMask.button);
    }
  }

  m_input.swap(m_previousInput);
}

void CSteamController::GetPeripheralInfo(ADDON::Peripheral& peripheralInfo)
{
  peripheralInfo.SetType(PERIPHERAL_TYPE_JOYSTICK);
  peripheralInfo.SetName(STEAM_CONTROLLER_NAME);
  peripheralInfo.SetVendorID(m_device->VendorID());
  peripheralInfo.SetProductID(m_device->ProductID());
  peripheralInfo.SetIndex(m_index);
}

void CSteamController::GetJoystickInfo(ADDON::Joystick& joystickInfo)
{
  GetPeripheralInfo(joystickInfo);

  joystickInfo.SetProvider(STEAM_CONTROLLER_PROVIDER);
  joystickInfo.SetButtonCount(0); // TODO
  joystickInfo.SetAxisCount(0); // TODO
  joystickInfo.SetMotorCount(2);
}

bool CSteamController::SendEvent(const ADDON::PeripheralEvent& event)
{
  switch (event.Type())
  {
  case PERIPHERAL_EVENT_TYPE_SET_MOTOR:
  {
    HapticPosition position = CSteamControllerTranslator::GetPosition(event.DriverIndex());

    AddFeedback(position, event.MotorState());

    return true;
  }
  default:
    break;
  }

  return false;
}

void CSteamController::AddFeedback(HapticPosition position, float magnitude)
{
  if (magnitude < 0.0f)
    magnitude = 0.0f;

  uint16_t amplitude = std::min(static_cast<int>(magnitude * 0xffff), static_cast<int>(0xffff));

  AddFeedback(position, amplitude);
}

void CSteamController::AddFeedback(HapticPosition position,
                                   uint16_t amplitude /* = 128 */,
                                   uint16_t period /* = 0 */,
                                   uint16_t count /* = 1 */)
{
  FeedbackMessage msg;
  msg.byte1 = 0x8f;
  msg.byte2 = 0x07;
  msg.position = static_cast<uint8_t>(position);
  msg.amplitude = amplitude;
  msg.amplitude = amplitude;
  msg.count = count;

  const uint8_t* data = reinterpret_cast<const uint8_t*>(&msg);

  std::vector<uint8_t> message(data, data + sizeof(msg));

  m_feedbackCallback->AddMessage(this, std::move(message));
}

void CSteamController::SendControl(const std::vector<uint32_t>& data, unsigned int timeout /* = 0 */)
{
  SendControl(reinterpret_cast<const uint8_t*>(data.data()), data.size(), timeout);
}

void CSteamController::SendControl(const uint8_t* data, size_t length, unsigned int timeout /* = 0 */)
{
  std::vector<uint8_t> buffer(64, 0);
  std::memcpy(const_cast<uint8_t*>(buffer.data()), data, std::min(length, buffer.size()));

  const uint8_t requestType = 0x21;
  const uint8_t request = 0x09;
  const uint16_t value = 0x0300;
  const uint16_t index = GetControlIdx();

  int transfered = m_deviceHandle->ControlWrite(requestType, request, value, index, buffer, timeout);
}

uint8_t CSteamController::GetEndpoint() const
{
  switch (m_device->ProductID())
  {
  case STEAM_CONTROLLER_PID_WIRELESS: return STEAM_CONTROLLER_ENDPOINT_WIRELESS;
  case STEAM_CONTROLLER_PID_WIRED:    return STEAM_CONTROLLER_ENDPOINT_WIRED;
  default:
    break;
  }

  return 0;
}

uint8_t CSteamController::GetControlIdx() const
{
  switch (m_device->ProductID())
  {
  case STEAM_CONTROLLER_PID_WIRELESS: return STEAM_CONTROLLER_CONTROLIDX_WIRELESS;
  case STEAM_CONTROLLER_PID_WIRED:    return STEAM_CONTROLLER_CONTROLIDX_WIRED;
  default:
    break;
  }

  return 0;
}
