cmake_minimum_required(VERSION 3.1)
project(peripheral.steamcontroller)

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

set(STEAMCONTROLLER_SOURCES src/addon.cpp)

list(APPEND DEPLIBS
    ${LIBUSB_1_LIBRARIES}
    ${COCOA_LIBRARY}
    ${FRAMEWORK_IOKIT}
)

# ------------------------------------------------------------------------------

build_addon(${PROJECT_NAME} STEAMCONTROLLER DEPLIBS)

