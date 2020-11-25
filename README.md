[![License: GPL-2.0-or-later](https://img.shields.io/badge/License-GPL%20v2+-blue.svg)](LICENSE.md)
[![Build Status](https://travis-ci.org/kodi-game/peripheral.steamcontroller.svg?branch=master)](https://travis-ci.org/kodi-game/peripheral.steamcontroller/branches)

# Steam controller driver for Kodi

![Steam controller](https://raw.githubusercontent.com/kodi-game/peripheral.steamcontroller/master/peripheral.steamcontroller/icon.png)

This is a peripheral add-on for Kodi that enables input from Steam controllers. It is based on the Standalone Steam Controller Driver: https://github.com/ynsta/steamcontroller.

## Building

Building this add-on requires Kodi's internal CMake-based build system for binary add-ons. If you are cross-compiling or just packaging the add-on, it is recommended that you use the Makefile provided with Kodi.

The Makefile will download, build and install the add-on and its dependencies. There is no need to manually clone the add-on if Kodi's source is available.

### Building on Linux

Make sure Kodi's add-on build system is installed somewhere. See https://github.com/xbmc/xbmc/blob/master/docs/README.md for instructions on building Kodi, which will create the binary add-on build system.

Run the Makefile with the path to the build system:

```shell
cd tools/depends/target/binary-addons
make PREFIX=$HOME/kodi ADDONS="peripheral.steamcontroller"
```

You can specify multiple add-ons, and wildcards are accepted too. For example, `ADDONS="pvr.*"` will build all pvr add-ons.

On Linux this performs a cross-compile install, so to package the add-on you'll need to copy the library and add-on files manually:

```shell
cd $HOME/workspace/kodi/addons
mkdir -p peripheral.steamcontroller
cp -r $HOME/kodi/share/kodi/addons/peripheral.steamcontroller/ .
cp -r $HOME/kodi/lib/kodi/addons/peripheral.steamcontroller/ .
```

To rebuild the add-on or compile a different one, clean the build directory:

```shell
make clean
```

### Building on OSX

Building on OSX is similar to Linux, but all the paths are determined for you. This command will download, build and install the add-on to the `addons/` directory in your Kodi repo:

```shell
cd tools/depends/target/binary-addons
make ADDONS="peripheral.steamcontroller"
```

### Building on Windows

First, download and install [CMake](http://www.cmake.org/download/).

To compile on windows, open a command prompt at `tools\buildsteps\win32` and run the script:

```
make-addons.bat install peripheral.steamcontroller
```

## Developing

When developing, compiling from a git repo is more convenient than repeatedly pushing changes to a remote one for Kodi's Makefile.

### Developing on Linux

```shell
git clone https://github.com/xbmc/peripheral.steamcontroller.git
cd peripheral.steamcontroller
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_INSTALL_PREFIX=$HOME/workspace/kodi/addons \
      -DPACKAGE_ZIP=1 \
      ..
make
make install
```

where `$HOME/workspace/kodi` symlinks to the directory you cloned Kodi into.

### Developing on Windows

This instructions here came from this helpful [forum post](http://forum.kodi.tv/showthread.php?tid=173361&pid=2097898#pid2097898).

First, open `tools\windows\prepare-binary-addons-dev.bat` and change `-DCMAKE_BUILD_TYPE=Debug ^` to `-DCMAKE_BUILD_TYPE=Release ^`.

Open a command prompt at `tools\windows` and run the script:

```shell
prepare-binary-addons-dev.bat peripheral.steamcontroller
```

Open `cmake\addons\build\kodi-addons.sln` and build the solution. This downloads the add-on from the version specified in its text file (see above) and creates a Visual Studio project for it. If the build fails, try running it twice.

This should package and copy the add-on to the `addons/` directory. If not, you can try opening the solution `cmake\addons\build\<addon-id>-prefix\src\<addon-id>-build\<addon-id>.sln` and building the INSTALL project or, worse case, copy by hand.
