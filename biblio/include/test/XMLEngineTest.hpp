#ifndef XMLENGINETEST_HPP
#define XMLENGINETEST_HPP
#include "ITest.hpp"
#include "SampleData.hpp"
#include "bib/XMLEngine.hpp"

using namespace std;
using bib::XMLEngine;

///
///\file SampleData.hpp
///\brief Test du XMLEngine
///\author matthieu
///


class XMLEngineTest : public ITest
{
public:
  void run(){
    cout <<"Stating XMLEngineTest" << endl;
    
    /** Saving a file */
    SampleData data1("Olivia","Megan", true, 51);
    XMLEngine::save<SampleData>(data1, "ofc", "osti.txt");
    cout <<"\tosti.txt written" << endl;
    
    /** Loading a file */    
    SampleData dataX = XMLEngine::load<SampleData>("ofc","osti.txt"); 
    cout <<"\t" << dataX.getID() << endl;
    cout <<"\t" << (dataX.getMeat().begin().operator*()) << endl;
  } 
};


#endif // XMLENGINETEST_HPP
