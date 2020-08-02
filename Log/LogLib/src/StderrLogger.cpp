#include "../include/StderrLogger.h"

void StderrLogger::class_log(const std::string& msg)
{
    std::cerr << msg << std::endl;
}

void StderrLogger::flush()
{
    std::cerr.flush();
}