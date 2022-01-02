/*
 *  Copyright (C) 2016-2021 Garrett Brown
 *  Copyright (C) 2016-2021 Team Kodi
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "Log.h"

#include <kodi/AddonBase.h>

#include <stdarg.h>
#include <stdio.h>

using namespace STEAMCONTROLLER;

#define MAXSYSLOGBUF  1024

CLog::CLog()
{
}

CLog& CLog::Get()
{
  static CLog instance;
  return instance;
}

void CLog::Log(LogLevel level, const char* format, ...)
{
  char buffer[MAXSYSLOGBUF];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer) - 1, format, args);
  va_end(args);

  ADDON_LOG addonLevel = ADDON_LOG_DEBUG;

  switch (level)
  {
  case LOG_DEBUG:
    addonLevel = ADDON_LOG_DEBUG;
    break;
  case LOG_INFO:
    addonLevel = ADDON_LOG_INFO;
    break;
  case LOG_ERROR:
    addonLevel = ADDON_LOG_ERROR;
    break;
  default:
    break;
  }

  kodi::Log(addonLevel, buffer);
}
