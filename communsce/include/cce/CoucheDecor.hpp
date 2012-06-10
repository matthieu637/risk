#ifndef COUCHEDECOR_HPP
#define COUCHEDECOR_HPP

#include <set>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Decor.hpp"

using sf::RenderTarget;

namespace cce
{

class CoucheDecor
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
    ///\brief Dessine les decors
    ///\param
    ///
	void dessiner(RenderTarget& cible);

    ///
    ///\brief Ajouter un decor aux coordonnees (x,y)
    ///\param le Decor, les coordonnees
    ///
        void addDecor(DecorTemplate *d, int x, int y);

    ///
    ///\brief Supprime un decor selon ses coordonnees
    ///\param Les coordonnees
    ///
        void removeDecor(int x, int y);
	
    private:
        std::set<cce::Decor> *decors;
};

} /* End of namespace cce */

#endif // COUCHEDECOR_HPP
