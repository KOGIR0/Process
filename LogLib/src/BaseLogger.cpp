#include "BaseLogger.h"

BaseLogger::BaseLogger(const Level& l) : level_(l){}

void BaseLogger::debug(const std::string& msg)
{
    log(msg, Level::DEBUG);
}

void BaseLogger::info(const std::string& msg)
{
    log(msg, Level::INFO);
}

void BaseLogger::warn(const std::string& msg)
{
    log(msg, Level::WARNING);
}

void BaseLogger::error(const std::string& msg)
{
    log(msg, Level::ERROR);
}

void BaseLogger::set_level(const Level& l)
{
    level_ = l;
}

Level BaseLogger::level()
{
    return level_;
}

void BaseLogger::log(const std::string& msg, const Level& l)
{
    if(level_ > l)
    {
        return;
    }

    class_log(msg);
}