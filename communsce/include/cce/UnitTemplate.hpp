#ifndef UNITTEMPLATE_HPP
#define UNITTEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <boost/serialization/nvp.hpp>
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "cce/AnimationTemplate.hpp"
#include <map>

using std::map;
using std::string;
using sf::Texture;
using boost::serialization::make_nvp;


namespace cce {

enum damage_type
{
    physical, laser, plasma, energy
};

enum defence_type
{
    tough, reflection, shield, massive
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
	ar & make_nvp("hp_max", hp_max);
	ar & make_nvp("path", path);
	ar & make_nvp("range", range);	
	
	ar & make_nvp("mapAnimTemplate", mapAnimTemplate);
	//boost::serialization::split_member(ar, *this, version);
    }
    
    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
// 	map<std::string,AnimationTemplate>  mapAnimTemplate;
// 	mapAnimTemplate["moveUp"] = AnimationTemplate("moveUp",0,0,6,64,47,1);
// 	mapAnimTemplate["moveRight"] = AnimationTemplate("moveRight",1,0,6,64,47,1);
// 	mapAnimTemplate["moveDown"] = AnimationTemplate("moveDown",2,0,6,64,47,1);
// 	mapAnimTemplate["moveLeft"] = AnimationTemplate("moveLeft",3,0,6,64,47,1);
// 	ar & make_nvp("mapAnimTemplate", mapAnimTemplate);
    }

    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
      
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

    void initAnimation();
    

///
///\brief attaques/seconde
///
    float getAttackSpeed();

///
///\brief Texture de la tile
///\return Retourne la texture de la tile
///
    Texture* getTexture();
    
///
///\brief Vitesse de déplacement en pixels/seconde?
///
    int getMoveSpeed();
 
//     AnimationTemplate* getMapTemplate();
    map<std::string,AnimationTemplate> * getMapTemplate();

    
///
///\brief Portée d'attaque de l'unité
///
    int getRange();
    
///
///\brief Portée d'attaque de l'unité
///
    int getHP();

private:
    int id, dmg_min, dmg_max, defence, move_speed, attack_speed, hp_max;
    string nom, description, path;
    bool collision_;
    float range;
    damage_type dmg_type;
    defence_type def_type;
    Texture *texture;
    map<std::string,AnimationTemplate>  mapAnimTemplate;
    
    sf::CircleShape* selection_circle;

};

}

#endif // UNITTEMPLATE_HPP
