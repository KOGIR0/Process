#include "BaseLogger.h"
#include <iostream>
#include <string>
#include <fstream>

namespace log
{
    class FileLogger : public BaseLogger
    {
    public:    
        FileLogger(const std::string& filename, lvl::Level l) : logFile(filename), BaseLogger(l){};
        void flush() override;

    private:
        std::ofstream logFile;
        void class_log(const std::string& msg) override;
    };
}