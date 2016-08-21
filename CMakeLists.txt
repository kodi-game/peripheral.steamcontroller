project(peripheral.steamcontroller)

cmake_minimum_required(VERSION 2.6)
enable_language(CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# --- Add-on Dependencies ------------------------------------------------------

find_package(Kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(libusb-1.0 REQUIRED)

# Fix linking on OSX
IF (APPLE)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(FRAMEWORK_IOKIT IOKit)
ENDIF (APPLE)

include_directories(${INCLUDES}
                    ${PROJECT_SOURCE_DIR}/src
                    ${KODI_INCLUDE_DIR}
                    ${kodiplatform_INCLUDE_DIRS}
                    ${LIBUSB_1_INCLUDE_DIRS})

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

list(APPEND DEPLIBS
    ${LIBUSB_1_LIBRARIES}
    ${COCOA_LIBRARY}
    ${FRAMEWORK_IOKIT}
)

# ------------------------------------------------------------------------------

build_addon(${PROJECT_NAME} STEAMCONTROLLER DEPLIBS)

include(CPack)
