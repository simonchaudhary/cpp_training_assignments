#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

using std::cout;
using std::string;

class Logger
{
public:
    static void log(const string &message); // Declaration of log method
};

#endif // LOGGER_H
