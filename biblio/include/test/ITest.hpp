#ifndef ITEST_HPP
#define ITEST_HPP

///
///\file SampleData.hpp
///\brief Interface à implémenter pour tous les tests à lancer
///\author matthieu
///


#include <iostream>

class ITest
{
public:
  virtual void run() = 0;
};

#endif // ITEST_HPP
