#ifndef BASELOGGER_H
#define BASELOGGER_H

#include <string>
#include <Level.h>

class BaseLogger
{
public:
    BaseLogger(const Level& l);

    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
    void set_level(const Level& l);
    Level level();
    virtual void flush() = 0;

    ~BaseLogger(){}

private:
    Level level_;

    void log(const std::string& msg, const Level& l);
    virtual void class_log(const std::string& msg) = 0;
};
#endif //BASELOGGER_H