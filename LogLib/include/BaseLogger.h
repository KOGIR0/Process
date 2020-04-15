#ifndef BASELOGGER_H
#define BASELOGGER_H

#include <string>
#include "Level.h"

namespace log
{

    class BaseLogger
    {
    public:
        BaseLogger(const lvl::Level& l);

        void debug(const std::string& msg);
        void info(const std::string& msg);
        void warn(const std::string& msg);
        void error(const std::string& msg);
        void set_level(const lvl::Level& l);
        lvl::Level level();

        virtual void flush() = 0;
        virtual ~BaseLogger(){};

    private:
        lvl::Level level_;

        void log(const std::string& msg, const lvl::Level& l);
        virtual void class_log(const std::string& msg) = 0;
    };
}

#endif //BASELOGGER_H