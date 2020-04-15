#include "FileLogger.h"


void log::FileLogger::class_log(const std::string& msg)
{
    logFile << msg << std::endl;
}

void log::FileLogger::flush()
{
    logFile.flush();
}