#include "BaseLogger.h"
#include <iostream>

namespace log
{
    class StdoutLogger : public BaseLogger
    {
    public:
        StdoutLogger(const lvl::Level& l) : BaseLogger(l) {}
        void flush() override;

    private:
        void class_log(const std::string& msg) override;
    };
}