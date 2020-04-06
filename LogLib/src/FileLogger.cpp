#include "FileLogger.h"


void FileLogger::class_log(const std::string& msg)
{
    logFile << msg << std::endl;
}

void FileLogger::flush()
{
    logFile.flush();
}

FileLogger::~FileLogger()
{
    logFile.close();
}