/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

namespace STEAMCONTROLLER
{
  class CUSBTransfer;

  /*!
   * \brief USB async Rx function
   */
  class ITransferCallback
  {
  public:
    virtual ~ITransferCallback() = default;

    virtual void OnTransferComplete(CUSBTransfer* transfer) = 0;
  };
}
