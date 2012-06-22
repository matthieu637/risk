#ifndef COUCHEDECOR_HPP
#define COUCHEDECOR_HPP

#include <set>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>

using sf::RenderTarget;
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
    ///\param x, y: coordonnees du decor à déplacer
    ///       x1, y1: coordonnees où le déplacer
    ///
    void moveDecor(int x, int y, int dx, int dy);

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

    ///
    ///\brief Supprime un decor selon ses coordonnees
    ///\param Les coordonnees
    ///
    void removeDecor(int x, int y);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    set<Decor> *decors;
    const Decor *d_move;
};

} /* End of namespace cce */

#endif // COUCHEDECOR_HPP
