#include <iostream>
#include <list>
#include "test/Test.hpp"
#include "test/XMLEngineTest.hpp"

using namespace std;

int main(){
  
  list<Test*> tests;
  
  /** Add further tests here */
  XMLEngineTest t;
  tests.push_back(&t);
  /** */
  
  for (list<Test*>::iterator it = tests.begin(); it != tests.end(); it++)
      (*it)->run();
  
  cout << "Tests ... done !" << endl;
  
  return 0;
}