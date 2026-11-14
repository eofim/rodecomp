#ifndef RAGNAROK_SOURCE_DEBUG_DEBUGLOG_H
#define RAGNAROK_SOURCE_DEBUG_DEBUGLOG_H

// Lightweight append-only diagnostic log for the standalone build. Not part of
// the original executable; writes rode_debug.log next to the running exe.
void DebugLog(const char* category, const char* format, ...);
void DebugLogRaw(const char* category, const char* text);

#endif
