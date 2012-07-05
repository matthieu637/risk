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
    
//     AnimationTemplate* getMapTemplate();
    map<std::string,AnimationTemplate> * getMapTemplate();
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
	
	ar & make_nvp("mapAnimTemplate", mapAnimTemplate);
//         boost::serialization::split_member(ar, *this, version);
    }
    
     template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
// 	map<std::string,AnimationTemplate>  mapAnimTemplate;
// 	 mapAnimTemplate["moveUp"] = AnimationTemplate("moveUp",0,64,47,1);
// 	 mapAnimTemplate["moveRight"] = AnimationTemplate("moveRight",1,64,47,1);
// 	 mapAnimTemplate["moveDown"] = AnimationTemplate("moveDown",2,64,47,1);
// 	 mapAnimTemplate["moveLeft"] = AnimationTemplate("moveLeft",3,64,47,1);
// 	ar & make_nvp("mapAnimTemplate", mapAnimTemplate);
    }

    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
      
    }

    
    void loadAfterXML(int id);
    
private:
    int id;
    bool bloquant_;
    string path;
    Texture *texture;

    map<std::string,AnimationTemplate>  mapAnimTemplate;
};

}
#endif // DECORTEMPLATE_HPP
