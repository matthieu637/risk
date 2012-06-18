#ifndef UPGRADETEMPLATE_HPP
#define UPGRADETEMPLATE_HPP

#include <string>
#include <boost/serialization/nvp.hpp>

using std::string;
using boost::serialization::make_nvp; 

namespace cce{

class UpgradeTemplate
{

public:
    UpgradeTemplate();
    void init(int _id, string nom);
    virtual ~UpgradeTemplate();
    
///
///\brief Description visible dans le client et l'editeur
///
    void setDescription(string description);
    
    int getID();
    string getNom();
    string getDescription();
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void)version;
	ar & make_nvp("id", id); 
        ar & make_nvp("nom", nom); 
	ar & make_nvp("description", description);
    }
    
    
private:
    int id;
    string nom, description;
};

}

#endif // UPGRADETEMPLATE_HPP
