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

#include <stdint.h>
#include <string>
#include <vector>

namespace STEAMCONTROLLER
{
  enum class InputStatus
  {
    INPUT   = 0x01,
    HOTPLUG = 0x03,
    IDLE    = 0x04,
  };

  class CSteamControllerInput
  {
  public:
    CSteamControllerInput();

    void Reset();

    bool Deserialize(const std::vector<uint8_t>& packet);

    InputStatus Status() const       { return static_cast<InputStatus>(m_state.status); }
    uint8_t     Seq() const          { return m_state.seq; }
    uint32_t    Buttons() const      { return m_state.buttons; }
    uint8_t     LeftTrigger() const  { return m_state.ltrig; }
    uint8_t     RightTrigger() const { return m_state.rtrig; }
    int16_t     LeftPadX() const     { return m_state.lpad_x; }
    int16_t     LeftPadY() const     { return m_state.lpad_y; }
    int16_t     RightPadX() const    { return m_state.rpad_x; }
    int16_t     RightPadY() const    { return m_state.rpad_y; }

  private:
    struct PacketFormat
    {
      uint8_t   unk_00;
      uint8_t   unk_01;
      uint8_t   status;
      uint8_t   unk_02;
      uint16_t  seq;
      uint8_t   unk_03;
      uint32_t  buttons;
      uint8_t   ltrig;
      uint8_t   rtrig;
      uint8_t   unk_04;
      uint8_t   unk_05;
      uint8_t   unk_06;
      int16_t   lpad_x;
      int16_t   lpad_y;
      int16_t   rpad_x;
      int16_t   rpad_y;
      uint8_t   unk_07[10];
      int16_t   gpitch;
      int16_t   groll;
      int16_t   gyaw;
      int16_t   q1;
      int16_t   q2;
      int16_t   q3;
      int16_t   q4;
      uint8_t   unk_08[16];
    } __attribute__((__packed__));

    PacketFormat m_state;
  };
}
