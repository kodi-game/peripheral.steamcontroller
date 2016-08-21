project(peripheral.steamcontroller)

cmake_minimum_required(VERSION 2.6)
enable_language(CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# --- Add-on Dependencies ------------------------------------------------------

find_package(Kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(libusb-1.0 REQUIRED)

include_directories(${INCLUDES}
                    ${PROJECT_SOURCE_DIR}/src
                    ${KODI_INCLUDE_DIR}
                    ${kodiplatform_INCLUDE_DIRS}
                    ${LIBUSB_1_INCLUDE_DIRS})

set(STEAMCONTROLLER_SOURCES src/addon.cpp)

list(APPEND DEPLIBS ${LIBUSB_1_LIBRARIES})

# ------------------------------------------------------------------------------

build_addon(${PROJECT_NAME} STEAMCONTROLLER DEPLIBS)

include(CPack)
