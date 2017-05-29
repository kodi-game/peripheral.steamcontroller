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

#include <memory>
#include <vector>

#define STEAM_CONTROLLER_NAME          "Steam Controller" // TODO: Get from USB device
#define STEAM_CONTROLLER_PROVIDER      "steam"

#define STEAM_CONTROLLER_VID           0x28de
#define STEAM_CONTROLLER_PID_WIRELESS  0x1142
#define STEAM_CONTROLLER_PID_WIRED     0x1102

#define STEAM_CONTROLLER_ENDPOINT_WIRELESS  2
#define STEAM_CONTROLLER_ENDPOINT_WIRED     3

#define STEAM_CONTROLLER_CONTROLIDX_WIRELESS  2
#define STEAM_CONTROLLER_CONTROLIDX_WIRED     1

#define STEAM_CONTROLLER_HPERIOD   0.02f
#define STEAM_CONTROLLER_LPERIOD   0.5f
#define STEAM_CONTROLLER_DURATION  1.0f

namespace STEAMCONTROLLER
{
  class CSteamController;
  typedef std::shared_ptr<CSteamController> ControllerPtr;
  typedef std::vector<ControllerPtr>        ControllerVector;

  /*!
   * \brief Specify which pad or trigger is used
   */
  enum class HapticPosition
  {
    RIGHT,
    LEFT,
  };
}
