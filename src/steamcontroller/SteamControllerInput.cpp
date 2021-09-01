/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "SteamControllerInput.h"

#include <cstring>

using namespace STEAMCONTROLLER;

#define PACKET_SIZE  64

CSteamControllerInput::CSteamControllerInput()
{
  static_assert(sizeof(m_state) == PACKET_SIZE, "Unexpected packet size!");

  Reset();
}

void CSteamControllerInput::Reset()
{
  std::memset(&m_state, 0x00, sizeof(m_state));
}

bool CSteamControllerInput::Deserialize(const std::vector<uint8_t>& packet)
{
  if (packet.size() != sizeof(m_state))
    return false;

  std::memcpy(&m_state, packet.data(), sizeof(m_state));

  return true;
}
