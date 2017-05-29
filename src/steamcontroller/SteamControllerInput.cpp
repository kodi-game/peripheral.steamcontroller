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
