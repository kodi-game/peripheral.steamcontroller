/*
 *  Copyright (C) 2016-2020 Garrett Brown
 *  Copyright (C) 2016-2020 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
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

    void Log(LogLevel level, const char* format, ...);
  };
}
