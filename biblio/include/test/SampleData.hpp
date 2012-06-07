#ifndef SAMPLEDATA_HPP
#define SAMPLEDATA_HPP

#include <list>
#include <string>

using std::list;
using std::string;

class SampleData
{

public:
    SampleData();
    
private:
   list<string> meat;
   bool hot;
   int id;
};

#endif // SAMPLEDATA_H
