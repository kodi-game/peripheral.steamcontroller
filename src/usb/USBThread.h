/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "steamcontroller/interfaces/IFeedbackCallback.h"

#include <list>
#include <mutex>
#include <stdint.h>
#include <thread>
#include <vector>

namespace STEAMCONTROLLER
{
  class CUSBContext;
  class CUSBDeviceHandle;
  class ISendMessageCallback;

  /*!
   * \brief Thread to run in order to process USB events
   */
  class CUSBThread : public IFeedbackCallback
  {
  public:
    CUSBThread(CUSBContext* context);
    ~CUSBThread() override;

    void Initialize() { }
    void Deinitialize();

    // implementation of IFeedbackCallback
    void RegisterDeviceHandle(CUSBDeviceHandle* deviceHandle) override;
    void UnregisterDeviceHandle(CUSBDeviceHandle* deviceHandle) override;
    void AddMessage(ISendMessageCallback* callback, std::vector<uint8_t>&& message) override;

  protected:
    // implementation of CThread
    void Process();

  private:
    struct FeedbackMessage
    {
      ISendMessageCallback* callback;
      std::vector<uint8_t>  data;
    };

    void SendMessage(const FeedbackMessage& message);

    // Construction parameter
    CUSBContext* const m_context;

    std::vector<CUSBDeviceHandle*> m_deviceHandles;

    std::list<FeedbackMessage> m_messagesIn;

    std::recursive_mutex m_mutex;
    std::thread* m_thread = nullptr;
    bool m_isStopped = true;
  };
}
