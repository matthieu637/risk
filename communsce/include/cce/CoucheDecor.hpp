#ifndef COUCHEDECOR_HPP
#define COUCHEDECOR_HPP

#include <set>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/set.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "cce/Decor.hpp"

using sf::RenderTarget;
using boost::serialization::make_nvp;
using std::set;

namespace cce
{

class Decor;
class DecorTemplate;

class CoucheDecor : public sf::Drawable
{
public:

    ///
    ///\brief Construit une couche vide.
    ///
    CoucheDecor ();
    virtual ~CoucheDecor ();

    ///
    ///\brief Decor visible en x,y
    ///\param x: abcisse
    ///       y: ordonnee
    ///\return le Decor aux coordonnees (x,y)
    ///
    const Decor* getDecor(int x, int y);

    ///
    ///\brief Deplace un decor.
    ///\param dx, dy: deplacemement du décor
    ///
    void moveDecor(int dx, int dy);


    ///
    ///\brief Initialise le decor à déplacer
    ///\param x, y: coordonnees du decor à déplacer
    ///
    void setDecorMove(int x, int y);

    ///
    ///\brief Dessine les decors
    ///\param
    ///
    void dessiner(RenderTarget& cible);

    ///
    ///\brief Ajouter un decor aux coordonnees (x,y)
    ///\param le Decor, les coordonnees
    ///\return le decor créé
    ///
    void addDecor(DecorTemplate *d, int x, int y);
    void addDecor(Decor *d);
    
    ///
    ///\brief Supprime un decor selon ses coordonnees
    ///\param Les coordonnees
    ///
    void removeDecor(int x, int y);

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
        ar & make_nvp("Decors", decors);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    set<Decor> decors;
    Decor *d_move;
};

} /* End of namespace cce */

#endif // COUCHEDECOR_HPP
