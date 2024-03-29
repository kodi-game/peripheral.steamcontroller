/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "SteamControllerTypes.h"
#include "usb/USBTypes.h"
#include "usb/interfaces/IMessageCallback.h"
#include "usb/interfaces/ISendMessageCallback.h"

#include <memory>
#include <stdint.h>
#include <vector>

namespace kodi
{
namespace addon
{
  class Joystick;
  class Peripheral;
  class PeripheralEvent;
}
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
    void OnTransferComplete(const std::vector<uint8_t>& message) override;

    // implementation of ISendMessageCallback
    void SendControl(const uint8_t* data, size_t length, unsigned int timeout = 0) override;

    // Peripheral interface
    void GetPeripheralInfo(kodi::addon::Peripheral& peripheralInfo);
    void GetJoystickInfo(kodi::addon::Joystick& joystickInfo);
    bool SendEvent(const kodi::addon::PeripheralEvent& event);

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

    double  m_lastUsbTimeMs;
    float   m_period;
  };
}
