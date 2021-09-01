/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
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
