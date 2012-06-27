#ifndef UNITTEMPLATE_HPP
#define UNITTEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <boost/serialization/nvp.hpp>

using std::string;
using sf::Texture;
using boost::serialization::make_nvp;


namespace cce {

enum damage_type
{
    normal, laser, percant
};

enum defence_type
{
    acier, bouclier, reflexion
};

class UnitTemplate
{

public:
    UnitTemplate();
    virtual ~UnitTemplate();
    
    void loadAfterXML(int _id);
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
        ar & make_nvp("dmg_min", dmg_min);
        ar & make_nvp("dmg_max", dmg_max);
	ar & make_nvp("defence", defence);
	ar & make_nvp("move_speed", move_speed);
	ar & make_nvp("attack_speed", attack_speed);
	ar & make_nvp("nom", nom);
	ar & make_nvp("description", description);
	ar & make_nvp("collision", collision_);
	ar & make_nvp("dmg_type", dmg_type);
	ar & make_nvp("def_type", def_type);
	ar & make_nvp("path", path);
    }
    

///
///\brief Description visible dans le client et l'editeur
///
    void setDescription(string description);

///
///\brief Si elle subit les collisions
///
    void setCollision(bool collision);

///
///\brief Intervalle de degats
///
    void setDamage(int dmg_min, int dmg_max);

///
///\brief Defense de l'unite
///
    void setDefence(int defence);

///
///\brief Vitesse d'attaque en attaques/seconde
///
    void setAttackSpeed(int attack_speed);

///
///\brief Vitesse de déplacement en pixels/seconde?
///
    void setMoveSpeed(int move_speed);

///
///\brief Type de degats
///
    void setDamageType(damage_type dmg_type);

///
///\brief Type de defense
///
    void setDefenseType(defence_type def_type);

    int getID();
    string getNom();
    string getDescription();
    bool collision();
    int getDamageMin();
    int getDamageMax();
    int getDefence();
    damage_type getDamageType();
    defence_type getDefenseType();

///
///\brief attaques/seconde
///
    float getAttackSpeed();

///
///\brief Vitesse de déplacement en pixels/seconde?
///
    int getMoveSpeed();

private:
    int id, dmg_min, dmg_max, defence, move_speed, attack_speed;
    string nom, description, path;
    bool collision_;
    damage_type dmg_type;
    defence_type def_type;
};

}

#endif // UNITTEMPLATE_HPP
