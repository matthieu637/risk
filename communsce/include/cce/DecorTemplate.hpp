#ifndef DECORTEMPLATE_HPP
#define DECORTEMPLATE_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_member.hpp>

#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "cce/AnimationTemplate.hpp"
#include <map>

using std::map;

using sf::Texture;
using boost::serialization::make_nvp;
using std::string;

namespace cce{

class DecorTemplate
{

public:
    DecorTemplate();
    virtual ~DecorTemplate();
    
///
///\brief Texture du Decor
///\return Retourne la texture du Decor
///
    Texture* getTexture();
    
///
///\brief ID du decor
///\return Retourne l'id du DecorTemplate
///
    int getID();
    
    //thor::Animator<sf::Sprite, std::string> *getAnimathor();
    AnimationTemplate* getMapTemplate();
    void initAnimation();
    
///
///\brief Le Decor est-elle passable?
///\return Retourne true si le Decor bloque le pathing
///
    bool bloquant();
    
///
///\brief path du fichier image associé
///\return path de l'image sous forme de string
///
    string getPath(){return path;}
    
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
	(void) version;
      
	ar & make_nvp("path", path);
	ar & make_nvp("bloquant", bloquant_);
    }
    
    void loadAfterXML(int id);
    
private:
    int id;
    bool bloquant_;
    string path;
    Texture *texture;
    //thor::Animator<sf::Sprite, std::string> *animathor;
    map<std::string,AnimationTemplate>  mapAnimTemplate;
};

}
#endif // DECORTEMPLATE_HPP
