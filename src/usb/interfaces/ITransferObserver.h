/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

namespace STEAMCONTROLLER
{
  class CUSBTransfer;

  /*!
   * \brief libusb callbacks
   */
  class ITransferObserver
  {
  public:
    virtual ~ITransferObserver() = default;

    virtual void BeforeSubmit(CUSBTransfer* transfer) = 0;
    virtual void AfterCompletion(CUSBTransfer* transfer) = 0;
  };
}
