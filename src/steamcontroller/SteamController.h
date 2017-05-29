/*
 *      Copyright (C) 2016 Garrett Brown
 *      Copyright (C) 2016 Team Kodi
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
#pragma once

#include "SteamControllerTypes.h"
#include "usb/USBTypes.h"
#include "usb/interfaces/IMessageCallback.h"
#include "usb/interfaces/ISendMessageCallback.h"

#include <memory>
#include <stdint.h>
#include <vector>

namespace ADDON
{
  class Joystick;
  class Peripheral;
  class PeripheralEvent;
}

namespace STEAMCONTROLLER
{
  class CSteamControllerInput;
  class IFeedbackCallback;

  class CSteamController : public IMessageCallback,
                           public ISendMessageCallback
  {
  public:
    CSteamController(const DevicePtr& device, unsigned int index, IFeedbackCallback* feedbackCallback);

    ~CSteamController();

    bool Initialize();
    void Deinitialize();

    unsigned int Index() const { return m_index; }
    CUSBDevice& Device() const { return *m_device; }

    // implementation of IMessageCallback
    virtual void OnTransferComplete(const std::vector<uint8_t>& message) override;

    // implementation of ISendMessageCallback
    virtual void SendControl(const uint8_t* data, size_t length, unsigned int timeout = 0) override;

    // Peripheral interface
    void GetPeripheralInfo(ADDON::Peripheral& peripheralInfo);
    void GetJoystickInfo(ADDON::Joystick& joystickInfo);
    bool SendEvent(const ADDON::PeripheralEvent& event);

    void SendControl(const std::vector<uint32_t>& data, unsigned int timeout = 0);

  private:
    struct FeedbackMessage
    {
      uint8_t byte1;
      uint8_t byte2;
      uint8_t position;
      uint16_t amplitude;
      uint16_t period;
      uint16_t count;
    } __attribute__((__packed__));

    void ClaimInterfaces();

    /*!
     * \brief Process SteamController inputs to generate events
     */
    void ProcessInput();

    /*!
     * \brief Add haptic feedback to be send on next USB tick
     *
     * \param int position     haptic to use
     * \param int magnitude    signal amplitude from 0.0 to 1.0
     */
    void AddFeedback(HapticPosition position, float magnitude);

    /*!
     * \brief Add haptic feedback to be send on next USB tick
     *
     * \param position     haptic to use
     * \param amplitude    signal amplitude from 0 to 65535
     * \param period       signal period from 0 to 65535
     * \param count        number of periods to play
     */
    void AddFeedback(HapticPosition position,
                     uint16_t amplitude = 128,
                     uint16_t period = 0,
                     uint16_t count = 1);

    // Utility functions
    uint8_t GetEndpoint() const;
    uint8_t GetControlIdx() const;

    // Construction parameters
    const DevicePtr          m_device;
    const unsigned int       m_index;
    IFeedbackCallback* const m_feedbackCallback;

    DeviceHandlePtr m_deviceHandle;

    std::unique_ptr<CSteamControllerInput> m_input;
    std::unique_ptr<CSteamControllerInput> m_previousInput;

    int64_t m_lastUsbTimeMs;
    float   m_period;
  };
}
