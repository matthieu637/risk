#include "bib/StringUtils.hpp"

namespace bib {

string rmNumber(const string s) {
    string result;
    for(unsigned int i=0; i < s.length() ; i++)
        if(s.at(i) < 48 || s.at(i) > 57)
            result += s.at(i);
    return result;
}

string rmFirstNumber(const string s) {
    string result;
    bool begin = true;

    for(unsigned int i=0; i < s.length() ; i++)
        if(s.at(i) < 48 || s.at(i) > 57) {
            result += s.at(i);
            begin = false;
        }
        else if(!begin)
            result += s.at(i);

    return result;
}
}
