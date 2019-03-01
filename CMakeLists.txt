cmake_minimum_required(VERSION 3.1)
project(peripheral.steamcontroller)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# --- Add-on Dependencies ------------------------------------------------------

find_package(Kodi REQUIRED)
find_package(libusb-1.0 REQUIRED)
find_package(p8-platform REQUIRED)

# Fix linking on OSX
IF (APPLE)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(FRAMEWORK_IOKIT IOKit)
ENDIF (APPLE)

include_directories(${INCLUDES}
                    ${PROJECT_SOURCE_DIR}/src
                    ${KODI_INCLUDE_DIR}/.. # HACK (see https://github.com/xbmc/peripheral.joystick/pull/112)
                    ${LIBUSB_1_INCLUDE_DIRS}
                    ${p8-platform_INCLUDE_DIRS})

set(STEAMCONTROLLER_SOURCES
    src/steamcontroller/SteamController.cpp
    src/steamcontroller/SteamControllerInput.cpp
    src/steamcontroller/SteamControllerManager.cpp
    src/steamcontroller/SteamControllerTranslator.cpp
    src/usb/USBConfiguration.cpp
    src/usb/USBContext.cpp
    src/usb/USBDevice.cpp
    src/usb/USBDeviceHandle.cpp
    src/usb/USBInterface.cpp
    src/usb/USBInterfaceSetting.cpp
    src/usb/USBThread.cpp
    src/usb/USBTransfer.cpp
    src/util/Log.cpp
    src/addon.cpp
)

set(STEAMCONTROLLER_HEADERS
    src/steamcontroller/interfaces/IFeedbackCallback.h
    src/steamcontroller/SteamController.h
    src/steamcontroller/SteamControllerInput.h
    src/steamcontroller/SteamControllerManager.h
    src/steamcontroller/SteamControllerTranslator.h
    src/steamcontroller/SteamControllerTypes.h
    src/usb/interfaces/IMessageCallback.h
    src/usb/interfaces/ISendMessageCallback.h
    src/usb/interfaces/ITransferCallback.h
    src/usb/interfaces/ITransferObserver.h
    src/usb/USBConfiguration.h
    src/usb/USBContext.h
    src/usb/USBDevice.h
    src/usb/USBDeviceHandle.h
    src/usb/USBInterface.h
    src/usb/USBInterfaceSetting.h
    src/usb/USBThread.h
    src/usb/USBTransfer.h
    src/usb/USBTypes.h
    src/util/Log.h
)

list(APPEND DEPLIBS
    ${LIBUSB_1_LIBRARIES}
    ${p8-platform_LIBRARIES}
    ${COCOA_LIBRARY}
    ${FRAMEWORK_IOKIT}
)

# ------------------------------------------------------------------------------

build_addon(${PROJECT_NAME} STEAMCONTROLLER DEPLIBS)

