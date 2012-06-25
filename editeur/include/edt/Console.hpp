#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "cce/Console.hpp"
#include "edt/Modele.hpp"

namespace edt{

  class Console : public cce::Console
  {
    public:
       Console(const std::string& conteneur,Modele *modele);
       
  private:
    string onSave(const string& s);
    string onOpen(const string& s);
    string onQuit(const string& s);
    string onRedimensionner(const string& s);
    
    Modele* m;
  };

}
#endif // CONSOLE_HPP