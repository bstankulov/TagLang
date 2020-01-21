#ifndef __LOGGER_H
#define __LOGGER_H
#pragma once

#include <ostream>
#include <iostream>
#include <exception>

class Logger {
    private:
        Logger();
        inline static const std::string OPENING_ERROR = "\033[1;31m";
        inline static const std::string CLOSING_ERROR = "\033[0m\n";
    public:
        static void Log(std::ostream& out, const std::string& message);

        static void Error(const std::string& message);

        static void Error(const std::string& message, const std::string& command);
};

#endif
