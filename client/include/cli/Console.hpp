#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "cce/Console.hpp"
#include "cli/Modele.hpp"

namespace cli {

class Console : public cce::Console
{
public:
    Console(Modele *modele);
    CEGUI::String onOpen(const CEGUI::String& s);
    CEGUI::String onQuit(const CEGUI::String& s);
private:

    Modele* m;
};

}
#endif // CONSOLE_HPP
