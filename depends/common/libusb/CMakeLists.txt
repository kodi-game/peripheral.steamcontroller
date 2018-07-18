cmake_minimum_required(VERSION 3.5)
project(libusb)

include(ExternalProject)

ExternalProject_Add(
    libusb
    SOURCE_DIR          ${CMAKE_SOURCE_DIR}
    CONFIGURE_COMMAND   <SOURCE_DIR>/bootstrap.sh
    COMMAND             <SOURCE_DIR>/configure
                            --prefix=${CMAKE_INSTALL_PREFIX}
                            --enable-static
                            --disable-shared
                            --with-pic
                            --disable-examples-build
                            --disable-tests-build
                            --with-pic
    INSTALL_COMMAND     ""
    BUILD_IN_SOURCE     1
)

install(CODE "execute_process(COMMAND make install WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})")
