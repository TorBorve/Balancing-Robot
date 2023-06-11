#pragma once

#ifdef NDEBUG
#define DISABLE_LOGGING 
#endif

#include <ArduinoLog.h>


namespace Logger {
bool setup();
}