#include "BaseLogger.h"
#include <iostream>
#include <string>
#include <fstream>

class FileLogger : public BaseLogger
{
public:    
    FileLogger(const std::string& filename, Level l) : logFile(filename), BaseLogger(l){};

    void class_log(const std::string& msg);
    void flush();

    ~FileLogger();

private:
    std::ofstream logFile;
};
