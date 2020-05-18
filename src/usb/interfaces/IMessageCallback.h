/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <stdint.h>
#include <vector>

namespace STEAMCONTROLLER
{
  /*!
   * \brief USB async Rx function
   */
  class IMessageCallback
  {
  public:
    virtual ~IMessageCallback() = default;

    virtual void OnTransferComplete(const std::vector<uint8_t>& message) = 0;
  };
}
