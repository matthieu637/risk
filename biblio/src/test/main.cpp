#include <iostream>
#include <list>
#include "test/ITest.hpp"
#include "test/XMLEngineTest.hpp"

using namespace std;

int main(){
  
  list<ITest*> tests;
  
  /** Add further tests here */
  XMLEngineTest t;
  tests.push_back(&t);
  /** */
  
  for (list<ITest*>::iterator it = tests.begin(); it != tests.end(); it++)
      (*it)->run();
  
  cout << "Tests ... Done !" << endl;
  
  return 0;
}