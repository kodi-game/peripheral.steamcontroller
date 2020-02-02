/*
 *      Copyright (C) 2016-2020 Garrett Brown
 *      Copyright (C) 2016-2020 Team Kodi
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
