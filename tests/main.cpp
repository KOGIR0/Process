#include <iostream>
#include "StdoutLogger.h"
#include "FileLogger.h"
#include "StderrLogger.h"
#include "Level.h"

int main()
{
    StdoutLogger l(Level::DEBUG);
    l.debug("stdout logger debug message.");
    l.info("stdout logger info message.");
    l.warn("stdout logger warning message.");
    l.error("stdout logger error message.");

    FileLogger fl("logfile.txt", Level::DEBUG);
    fl.debug("file logger debug message.");
    fl.info("file logger info message.");
    fl.warn("file logger warning message.");
    fl.error("file logger error message.");

    StderrLogger el(Level::DEBUG);
    el.debug("stderror logger debug message.");
    el.info("stderror logger info message.");
    el.warn("stderror  logger warning message.");
    el.error("stderror logger error message.");

    fl.set_level(Level::INFO);
    fl.debug("file logger debug message.(Level: info)");
    fl.info("file logger info message.(Level: info)");
    fl.warn("file logger warning message.(Level: info)");
    fl.error("file logger error message.(Level: info)");

    l.set_level(Level::ERROR);
    l.debug("stdout logger debug message.(Level: error)");
    l.info("stdout logger info message.(Level: error)");
    l.warn("stdout logger warning message.(Level: error)");
    l.error("stdout logger error message.(Level: error)");

    return 0;
}
