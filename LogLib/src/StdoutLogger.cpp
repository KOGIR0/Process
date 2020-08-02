#include "StdoutLogger.h"

void log::StdoutLogger::class_log(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void log::StdoutLogger::flush()
{
    std::cout.flush();
}