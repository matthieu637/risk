#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "cce/Console.hpp"
#include "cli/Modele.hpp"

namespace cli {

class Console : public cce::Console
{
public:
    Console(const std::string& conteneur,Modele *modele);
    string onOpen(const string& s);
    string onQuit(const string& s);
private:

    Modele* m;
};

}
#endif // CONSOLE_HPP
