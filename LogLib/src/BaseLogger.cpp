#include "BaseLogger.h"

log::BaseLogger::BaseLogger(const lvl::Level& l) : level_(l){}

void log::BaseLogger::debug(const std::string& msg)
{
    log(msg, lvl::Level::DEBUG);
}

void log::BaseLogger::info(const std::string& msg)
{
    log(msg, lvl::Level::INFO);
}

void log::BaseLogger::warn(const std::string& msg)
{
    log(msg, lvl::Level::WARNING);
}

void log::BaseLogger::error(const std::string& msg)
{
    log(msg, lvl::Level::ERROR);
}

void log::BaseLogger::set_level(const lvl::Level& l)
{
    level_ = l;
}

lvl::Level log::BaseLogger::level()
{
    return level_;
}

void log::BaseLogger::log(const std::string& msg, const lvl::Level& l)
{
    if(level_ > l)
    {
        return;
    }

    class_log(msg);
}