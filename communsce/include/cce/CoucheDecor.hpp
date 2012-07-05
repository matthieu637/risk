#ifndef COUCHEDECOR_HPP
#define COUCHEDECOR_HPP

#include <set>
#include <stack>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/set.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "cce/Decor.hpp"

using sf::RenderTarget;
using boost::serialization::make_nvp;
using std::set;
using std::stack;

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
    Decor* getDecor(int x, int y);

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

    ///
    ///\brief please dont send me a local object
    ///
    void addDecor(Decor *d);

    ///
    ///\brief Supprime un decor selon ses coordonnees
    ///\param Les coordonnees
    ///
    void removeDecor(int x, int y);
    
     ///
    ///\brief Annule le dernier décor de la pile undoDecors
    ///
    void undoDecor();
    
    ///
    ///\brief Rétablie la derniere action de la pile undoDecors et l'ajoute dans redoDecors
    ///
    void redoDecor();
    
    ///
    ///\brief Efface les actions de la pile redoDecors
    ///
    void clearRedoDecors();
    
    ///
    ///\brief Supprime un decor selon son pointeur
    ///\param Le Decor à enlever
    ///
    void removeDecor(Decor* d);

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
        ar & make_nvp("Decors", decors);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();


    struct CompareDecorPtr
    {
        bool operator()(Decor* obj1, Decor* obj2) const
        {
            return obj1->inferieurA(*obj2);
        }
    };

protected:
    
    set<Decor*, CompareDecorPtr> decors;

    stack<Decor*> undoDecors; 
    stack<Decor*> redoDecors;
    
public:
    Decor* d_move;
};

} /* End of namespace cce */

#endif // COUCHEDECOR_HPP
