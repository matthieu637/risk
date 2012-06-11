#ifndef UNITTEMPLATE_HPP
#define UNITTEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>

using std::string;
using sf::Texture;

namespace cce{

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
    void init(int _id, string nom, bool collision = true);
    virtual ~UnitTemplate();
    
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
    void setAttackSpeed(float attack_speed);
    
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
    int id, dmg_min, dmg_max, defence, move_speed;
    float attack_speed;
    string nom, description;
    bool collision_;
    damage_type dmg_type;
    defence_type def_type;
};

}

#endif // UNITTEMPLATE_HPP
