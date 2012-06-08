#ifndef LOGGER_HPP
#define LOGGER_HPP

///
///\file Logger.hpp
///\brief Singleton de Logger afin d'écrire des logs
///\author matthieu
///\example Dans LoggerTest.hpp
///
///

#include <iostream>
#include <sstream>
#include <string>
#include "Singleton.hpp"


#define LOG_DEBUG(stream) \
  bib::Logger::getInstance()->isEnabled(bib::Logger::DEBUGGING) && std::cout << "DEBUG :" << __FILE__ << "."<< __LINE__ << " : " << stream << std::endl

#define LOG_INFO(stream) \
  bib::Logger::getInstance()->isEnabled(bib::Logger::INFO) && std::cout << "INFO :" << __FILE__ << "."<< __LINE__ << " : " << stream << std::endl

#define LOG_WARNING(stream) \
  bib::Logger::getInstance()->isEnabled(bib::Logger::WARNING) && std::cout << "WARNING :" << __FILE__ << "."<< __LINE__ << " : " << stream << std::endl

#define LOG_ERROR(stream) \
  bib::Logger::getInstance()->isEnabled(bib::Logger::ERROR) && std::cout << "ERROR :" << __FILE__ << "."<< __LINE__ << " : " << stream << std::endl



namespace bib {

class Logger : public Singleton<Logger> {
    friend class Singleton<Logger>;

public:
    enum LogLevel { DEBUGGING, INFO, WARNING, ERROR };

    bool isEnabled(LogLevel l) {
        return level <= l;
    }

    void setLevel(LogLevel l) {
        level = l;
    }

protected:
    Logger():level(INFO) {}

private :
    LogLevel level;
};

}


#endif
