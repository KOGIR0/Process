#include "StdoutLogger.h"

void StdoutLogger::class_log(const std::string& msg)
{
    std::cout << msg << std::endl;
}

void flush()
{
    std::cout.flush();
}