#ifndef TEST_HPP
#define TEST_HPP

///
///\file Test.hpp
///\brief Interface à implémenter pour tous les tests à lancer
///\author matthieu
///


#include <iostream>
#include <typeinfo>

using namespace std;

class Test
{
public:
  void run(){
   cout <<"Starting " << typeid(*this).name() << endl;
   runtest(); 
   cout << typeid(*this).name() << " done !" << endl;
  }
  
protected:
  virtual void runtest() = 0;
};

#endif // ITEST_HPP
