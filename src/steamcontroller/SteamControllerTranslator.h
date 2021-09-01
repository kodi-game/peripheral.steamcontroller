/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "SteamControllerTypes.h"

namespace STEAMCONTROLLER
{
  class CSteamControllerTranslator
  {
  public:
    static HapticPosition GetPosition(unsigned int motorIndex);
  };
}
