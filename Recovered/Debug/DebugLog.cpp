// Standalone diagnostic logger. Not a decompiled unit: the original executable
// has no equivalent. Compiled only into the local exe (EXE_ONLY_UNITS).
#include "Debug/DebugLog.h"

#include <windows.h>

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace {

const char* LogPath() {
  // Resolve once to the exe's own directory so the log lands next to Ragexe.exe
  // regardless of the working directory the client is launched with.
  static char path[MAX_PATH] = {};
  if (path[0] == '\0') {
    char module[MAX_PATH] = {};
    const DWORD length = GetModuleFileNameA(nullptr, module, MAX_PATH);
    char* slash = (length > 0) ? strrchr(module, '\\') : nullptr;
    if (slash) {
      *slash = '\0';
      std::snprintf(path, sizeof(path), "%s\\rode_debug.log", module);
    } else {
      std::snprintf(path, sizeof(path), "rode_debug.log");
    }
  }
  return path;
}

CRITICAL_SECTION& LogLock() {
  static CRITICAL_SECTION lock;
  static const bool initialized = [] {
    InitializeCriticalSection(&lock);
    return true;
  }();
  (void)initialized;
  return lock;
}

void WriteStamp(std::FILE* file, const char* category) {
  SYSTEMTIME now;
  GetLocalTime(&now);
  std::fprintf(
    file, "[%04d-%02d-%02d %02d:%02d:%02d.%03d] [%s] ", now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond, now.wMilliseconds,
    category ? category : "-"
  );
}

}  // namespace

void DebugLog(const char* category, const char* format, ...) {
  EnterCriticalSection(&LogLock());
  if (std::FILE* file = std::fopen(LogPath(), "a")) {
    WriteStamp(file, category);
    va_list args;
    va_start(args, format);
    std::vfprintf(file, format, args);
    va_end(args);
    std::fputc('\n', file);
    std::fclose(file);
  }
  LeaveCriticalSection(&LogLock());
}

void DebugLogRaw(const char* category, const char* text) {
  EnterCriticalSection(&LogLock());
  if (std::FILE* file = std::fopen(LogPath(), "a")) {
    WriteStamp(file, category);
    std::fputs("\n", file);
    std::fputs(text ? text : "(null)", file);
    std::fputs("\n----------------------------------------\n", file);
    std::fclose(file);
  }
  LeaveCriticalSection(&LogLock());
}
