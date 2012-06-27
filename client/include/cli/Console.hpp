#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "cce/Console.hpp"
#include "cli/Modele.hpp"

namespace cli {

class Console : public cce::Console
{
public:
    Console(Modele *modele);
    string onOpen(const std::string& s);
    string onQuit(const std::string& s);
    string onSpawn(const std::string& s);
private:

    Modele* m;
};

}
#endif // CONSOLE_HPP
