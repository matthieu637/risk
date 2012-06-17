#ifndef GUIEDITEUR_HPP
#define GUIEDITEUR_HPP
#include <cce/GUI.hpp>

namespace edt{
  
class GUI : public cce::GUI
{

public:
GUI(const string& conteneur_);
virtual ~GUI();
};

}

#endif // GUIEDITEUR_HPP
