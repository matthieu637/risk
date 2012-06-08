#ifndef TEST_HPP
#define TEST_HPP

///
///\file Test.hpp
///\brief Interface à implémenter pour tous les tests à lancer
///\author matthieu
///


#include <iostream>
#include <typeinfo>
#include "bib/StringUtils.hpp"

using namespace std;

class Test
{
public:
  void run(){
   cout <<"Starting " << bib::rmFirstNumber(typeid(*this).name()) << endl;
   runtest(); 
   cout << bib::rmFirstNumber(typeid(*this).name()) << " done !" << endl << endl;
  }
  
protected:
  virtual void runtest() = 0;

};

#endif // ITEST_HPP
