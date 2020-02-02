/*
 *      Copyright (C) 2016-2020 Garrett Brown
 *      Copyright (C) 2016-2020 Team Kodi
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

  AddonLog addonLevel = ADDON_LOG_DEBUG;

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
