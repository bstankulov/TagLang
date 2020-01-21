#ifndef __LOGGER_CPP
#define __lOGGER_CPP
#pragma once

#include "logger.h"

void Logger::Log(std::ostream& out, const std::string& message) {
    out << message << '\n';
} 

void Logger::Error(const std::string& message) {
    std::cerr << OPENING_ERROR << message << CLOSING_ERROR <<'\n';
    throw new std::invalid_argument(message);
}

void Logger::Error(const std::string& message, const std::string& command) {
    std::cerr << OPENING_ERROR << message << CLOSING_ERROR <<'\n';
    throw new std::invalid_argument(message);
}

#endif