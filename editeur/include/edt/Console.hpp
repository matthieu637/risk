#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "cce/Console.hpp"
#include "edt/Modele.hpp"


namespace edt {

class Console : public cce::Console
{
public:
    Console(Modele *modele);
    void afficherCommande(const string& s);
    
protected:
    void ParseText(const CEGUI::String& inMsg);
    
private:
    string onSave(const string& s);
    string onOpen(const string& s);
    string onQuit(const string& s);
    string onRedimensionner(const string& s);
    string onNewMap(const string& s);
    
    

    Modele* m;
};

}
#endif // CONSOLE_HPP
