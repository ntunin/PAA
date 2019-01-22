#include "stdafx.h"
#include "Log.h"

Log *Log::shared = NULL;

Log::Log()
{
}


Log::~Log()
{
}


Log *Log::getSharedLog() {
	return Log::shared;
}

void Log::setSharedLog(Log *log) {
	Log::shared = log;
}