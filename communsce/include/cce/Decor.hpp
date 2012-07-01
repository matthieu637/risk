#ifndef DECOR_HPP
#define DECOR_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <boost/serialization/nvp.hpp>
#include <Thor/Animation.hpp>
#include "DecorTemplate.hpp"
#include "Univers.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>

using sf::Texture;
using sf::Sprite;
using boost::serialization::make_nvp;

namespace cce {

class DecorTemplate;

class Decor : public Sprite
{

public:
    Decor(DecorTemplate *_dt, int x, int y);
    Decor();
    virtual ~Decor();

///
///\brief Retourne le Template de la tile
///\return Retourne le Template de la tile
///
    DecorTemplate* getTemplate() const;

///
///\brief Comparaison pour la position dans l'arbre
///\return True si ce decor vient avant d
///
    bool inferieurA(const Decor& d) const;

///
///\brief Changer la texture de l'objet (ajuste yCompare pour la position dans l'arbre)
///
    void setTexture(Texture* texture);
    
    void move(float offsetX, float offsetY);
    void animate();
    
    ///
    ///\brief Permet de reset la clock de l'animation pour une ré-insertion dans l'arbre décors
    void unpause();
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        boost::serialization::split_member(ar, *this, version);
    }

    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        (void) version;
        (void) ar;
        int id = dt->getID();
	int x = getPosition().x;
	int y = getPosition().y;
	
        ar << make_nvp("id", id);
	ar << make_nvp("x", x);
	ar << make_nvp("y", y);
    }

    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
        (void) file_version;
        (void) ar;
        int id, x, y;
        ar >> make_nvp("id", id);
	ar >> make_nvp("x", x);
	ar >> make_nvp("y", y);
	
	dt = Univers::getInstance()->getDecorTemplate(id);
	setTexture(dt->getTexture());
	setPosition(x, y);
    }

public:
    int yCompare;

protected:
    DecorTemplate *dt;
    
protected:
    thor::Animator<sf::Sprite, std::string> animation;
    sf::Clock frameClock;
};

bool operator<(Decor const &d1, Decor const &d2);

}
#endif // DECOR_HPP
