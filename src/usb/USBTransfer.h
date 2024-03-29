/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <stdint.h>
#include <string>
#include <vector>

struct libusb_device_handle;
struct libusb_transfer;

namespace STEAMCONTROLLER
{
  class ITransferCallback;
  class ITransferObserver;

  /*!
   * \brief USB asynchronous transfer control & data
   */
  class CUSBTransfer
  {
  public:
    CUSBTransfer(libusb_device_handle* handle, unsigned int isoPackets, ITransferObserver* observer);

    ~CUSBTransfer();

    void Close();

    /*!
     * \brief Prevent transfer from being submitted again
     */
    void Doom();

    /*!
     * \brief Setup transfer for interrupt use
     *
     * param endpoint       Endpoint to submit transfer to. Defines transfer direction
     *                      (see LIBUSB_ENDPOINT_OUT and LIBUSB_ENDPOINT_IN)
     *
     * \param bufferLength  Expected data length (when receiving data)
     * \param buffer        A string (when sending data)
     *
     * \param callback      Callback function to be invoked on transfer completion
     *
     * \param timeoutMs     Transfer timeout in milliseconds, or 0 to disable
     */
    bool SetInterrupt(uint8_t endpoint, unsigned int bufferLength, ITransferCallback* callback, unsigned int timeoutMs = 0);
    bool SetInterrupt(uint8_t endpoint, const std::string& buffer, ITransferCallback* callback, unsigned int timeoutMs = 0);

    /*!
     * \brief Get transfer status
     *
     * Should not be called on a submitted transfer.
     */
    int Status() const;

    /*!
     * \brief Get actually transfered data length
     *
     * Should not be called on a submitted transfer.
     */
    int ActualLength() const;

    /*!
     * \brief Get data buffer content
     *
     * Should not be called on a submitted transfer.
     */
    std::vector<uint8_t> Buffer() const;

    /*!
     * \brief Tells if this transfer is submitted and still pending
     */
    bool IsSubmitted() const;

    /*!
     * \brief Submit transfer for asynchronous handling
     */
    bool Submit();

    /*!
     * \brief Cancel transfer
     *
     * Note: cancellation happens asynchronously, so you must wait for
     * LIBUSB_TRANSFER_CANCELLED.
     */
    void Cancel();

  private:
    /*!
     * \brief Makes it possible for user-provided callback to alter transfer
     *        when fired (ie, mark transfer as not submitted upon call)
     */
    void TransferCallback(libusb_transfer* transfer);

    static void transfer_cb_fn(libusb_transfer* transfer);

    // Construction params
    libusb_device_handle* const m_handle;
    ITransferObserver* const m_observer;

    bool m_bInitailized;
    bool m_bSubmitted;
    bool m_bDoomed;
    std::string m_transferBuffer;
    ITransferCallback* m_callback;
    libusb_transfer* m_transfer;
  };
}
