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

#include "USBTypes.h"
#include "usb/interfaces/ITransferCallback.h"
#include "usb/interfaces/ITransferObserver.h"

#include <map>
#include <set>
#include <stdint.h>
#include <vector>

struct libusb_device_handle;

namespace STEAMCONTROLLER
{
  class IMessageCallback;

  /*!
   * \brief Represents an opened USB device
   */
  class CUSBDeviceHandle : public ITransferObserver,
                           public ITransferCallback
  {
  public:
    CUSBDeviceHandle(libusb_device_handle* handle);

    ~CUSBDeviceHandle();

    /*!
     * \brief Close this handle
     *
     * This method cancels any in-flight transfer when it is called. As
     * cancellation is not immediate, this method needs to let libusb handle
     * events until transfers are actually cancelled.
     *
     * In multi-threaded programs, this can lead to stalls. To avoid this,
     * do not close nor let GC collect a USBDeviceHandle which has in-flight
     * transfers.
     */
    void Close();

    // implementation of ITransferObserver
    virtual void BeforeSubmit(CUSBTransfer* transfer) override;
    virtual void AfterCompletion(CUSBTransfer* transfer) override;

    // implementation of ITransferCallback
    virtual void OnTransferComplete(CUSBTransfer* transfer) override;

    /*!
     * \brief Claim (get exclusive access to) given interface number
     *
     * Required to receive/send data.
     */
    bool ClaimInterface(unsigned int interfaceNumber);

    /*!
     * \brief Release interface, allowing another process to use it
     */
    void ReleaseInterface(unsigned int interfaceNumber);

    /*!
     * \brief Tell whether a kernel driver is active on given interface number
     */
    bool IsKernelDriverActive(unsigned int interfaceNumber);

    /*!
     * \brief Ask kernel driver to detach from given interface number
     */
    bool DetachKernelDriver(unsigned int interfaceNumber);

    /*!
     * \brief Initialize a USB transfer instance for asynchronous use
     *
     * \param endpoint The USB endpoint
     * \param iso_packets The number of isochronous transfer descriptors to allocate
     */
    void InitializeTransfer(IMessageCallback* callback, uint8_t endpoint, unsigned int isoPackets = 0);

    /*!
     * \brief Return true if any transfers are in flight
     */
    bool HasSubmittedTransfers();

    /*!
     * \brief Synchronous control read
     *
     * \sa ControlTransfer()
     */
    int ControlRead(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const std::vector<uint8_t>& data, unsigned int timeoutMs = 0);

    /*!
     * \brief Synchronous control write
     *
     * \sa ControlTransfer()
     */
    int ControlWrite(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const std::vector<uint8_t>& data, unsigned int timeoutMs = 0);

  private:
    /*!
     * \brief Synchronous control transfer
     *
     * \param requestType Request byte bitmask, see constants TYPE_* and RECIPIENT_*
     * \param request Request ID (some values are standard)
     * \param value meaning is request-dependent
     * \param index meaning is request-dependent
     * \param data meaning is request-dependent
     * \param timeoutMs How long to wait for device acknowledgement, or 0 to disable
     *
     * \return Number of bytes actually sent
     */
    int ControlTransfer(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const std::vector<uint8_t>& data, unsigned int timeoutMs);

    std::map<TransferPtr, IMessageCallback*> m_transfers;

    // In-flight transfers
    std::set<CUSBTransfer*> m_inflightTransfers;

    // Construction parameters
    libusb_device_handle* m_handle;
  };
}
