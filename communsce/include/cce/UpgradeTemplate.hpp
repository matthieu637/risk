#ifndef UPGRADETEMPLATE_HPP
#define UPGRADETEMPLATE_HPP

#include <string>

using std::string;

namespace cce{

class UpgradeTemplate
{

public:
    UpgradeTemplate(int _id, string nom);
    virtual ~UpgradeTemplate();
    
///
///\brief Description visible dans le client et l'editeur
///
    void setDescription(string description);
    
    int getID();
    string getNom();
    string getDescription();
    
private:
    int id;
    string nom, description;
};

}

#endif // UPGRADETEMPLATE_HPP
