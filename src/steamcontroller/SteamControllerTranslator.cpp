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

#include "SteamControllerTranslator.h"

using namespace STEAMCONTROLLER;

#define MOTOR_RIGHT_INDEX  0
#define MOTOR_LEFT_INDEX   1

HapticPosition CSteamControllerTranslator::GetPosition(unsigned int motorIndex)
{
  switch (motorIndex)
  {
  case MOTOR_RIGHT_INDEX: return HapticPosition::RIGHT;
  case MOTOR_LEFT_INDEX:  return HapticPosition::LEFT;
  default:
    break;
  }

  return HapticPosition::RIGHT;
}
