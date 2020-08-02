#include "BaseLogger.h"
#include <iostream>

class StdoutLogger : public BaseLogger
{
public:
    StdoutLogger(const Level& l) : BaseLogger(l) {}

    virtual void class_log(const std::string& msg);
    virtual void flush(){};

    ~StdoutLogger(){}
};
