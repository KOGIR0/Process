#include "StderrLogger.h"

void log::StderrLogger::class_log(const std::string& msg)
{
    std::cerr << msg << std::endl;
}

void log::StderrLogger::flush()
{
    std::cerr.flush();
}