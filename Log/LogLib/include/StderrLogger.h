#include "BaseLogger.h"
#include <iostream>
#include <string>

class StderrLogger : public BaseLogger
{
public:
    StderrLogger(const Level& l) : BaseLogger(l){}

    void class_log(const std::string& msg);
    void flush();
};
