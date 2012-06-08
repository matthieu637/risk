#include <iostream>
#include <list>
#include "test/Test.hpp"
#include "test/XMLEngineTest.hpp"
#include "test/LoggerTest.hpp"

using namespace std;

int main() {

    list<Test*> tests;

    /** Add further tests here */
    XMLEngineTest t0;
    LoggerTest t1;

    tests.push_back(&t0);
    tests.push_back(&t1);
    /** */

    for (list<Test*>::iterator it = tests.begin(); it != tests.end(); it++)
        (*it)->run();

    cout << "Tests ... done !" << endl;

    return 0;
}
