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

#include "steamcontroller/interfaces/IFeedbackCallback.h"

#include "p8-platform/threads/threads.h"

#include <list>
#include <stdint.h>
#include <vector>

namespace STEAMCONTROLLER
{
  class CUSBContext;
  class CUSBDeviceHandle;
  class ISendMessageCallback;

  /*!
   * \brief Thread to run in order to process USB events
   */
  class CUSBThread : public IFeedbackCallback,
                     protected P8PLATFORM::CThread
  {
  public:
    CUSBThread(CUSBContext* context);

    ~CUSBThread() { Deinitialize(true); }

    void Initialize() { }
    void Deinitialize(bool bWait);

    // implementation of IFeedbackCallback
    virtual void RegisterDeviceHandle(CUSBDeviceHandle* deviceHandle) override;
    virtual void UnregisterDeviceHandle(CUSBDeviceHandle* deviceHandle) override;
    virtual void AddMessage(ISendMessageCallback* callback, std::vector<uint8_t>&& message) override;

  protected:
    // implementation of CThread
    virtual void* Process() override;

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

    P8PLATFORM::CMutex m_mutex;
    P8PLATFORM::CEvent m_deviceAddEvent;
  };
}
