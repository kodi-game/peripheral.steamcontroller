project(peripheral.steamcontroller)

cmake_minimum_required(VERSION 2.6)
enable_language(CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# --- Add-on Dependencies ------------------------------------------------------

find_package(kodi REQUIRED)
find_package(LibUSB REQUIRED)

include_directories(${INCLUDES}
                    ${PROJECT_SOURCE_DIR}/src
                    ${KODI_INCLUDE_DIR}
                    ${LibUSB_INCLUDE_DIRS})

set(STEAMCONTROLLER_SOURCES src/addon.cpp)

list(APPEND DEPLIBS ${LibUSB_LIBRARIES})

# ------------------------------------------------------------------------------

build_addon(peripheral.steamcontroller STEAMCONTROLLER DEPLIBS)

include(CPack)
