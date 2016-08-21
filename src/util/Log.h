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

#ifndef dsyslog
#define dsyslog(...) STEAMCONTROLLER::CLog::Get().Log(STEAMCONTROLLER::LOG_DEBUG, __VA_ARGS__)
#endif

#ifndef isyslog
#define isyslog(...) STEAMCONTROLLER::CLog::Get().Log(STEAMCONTROLLER::LOG_INFO, __VA_ARGS__)
#endif

#ifndef esyslog
#define esyslog(...) STEAMCONTROLLER::CLog::Get().Log(STEAMCONTROLLER::LOG_ERROR, __VA_ARGS__)
#endif

namespace ADDON
{
  class CHelper_libXBMC_addon;
}

namespace STEAMCONTROLLER
{
  enum LogLevel
  {
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR,
  };

  class CLog
  {
    CLog();

  public:
    static CLog& Get();

    void Initailize(ADDON::CHelper_libXBMC_addon* frontend);
    void Deinitailize();

    void Log(LogLevel level, const char* format, ...);

  private:
    ADDON::CHelper_libXBMC_addon* m_frontend;
  };
}
