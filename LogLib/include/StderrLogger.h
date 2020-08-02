#include "BaseLogger.h"
#include <iostream>
#include <string>

namespace log
{
    class StderrLogger : public BaseLogger
    {
    public:
        StderrLogger(const lvl::Level& l) : BaseLogger(l){}
        void flush() override;
        
    private:
        void class_log(const std::string& msg) override;
    };
}