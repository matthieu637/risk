#ifndef LOGGERTEST_HPP
#define LOGGERTEST_HPP
#include "Test.hpp"

#define LOG_LEVEL 
#include "bib/Logger.hpp"

///
///\file LoggerTest.hpp
///\brief Test du XMLEngine
///\author matthieu
///

using bib::Logger;

class LoggerTest : public Test
{
public:
  void runtest(){
    
    int i = 5;
   
    Logger::getInstance()->setLevel(Logger::INFO);
    
    LOG_DEBUG("image toto chargée " << i << " test");
    LOG_INFO("image toto chargée ");
  } 
};


#endif // LOGGERTEST_HPP
