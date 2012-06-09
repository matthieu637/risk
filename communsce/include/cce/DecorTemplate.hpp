#ifndef DECORTEMPLATE_HPP
#define DECORTEMPLATE_HPP

namespace cce{

class DecorTemplate
{

public:
    DecorTemplate(int _id, bool _bloquant, Texture *_texture);
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
    
///
///\brief Le Decor est-elle passable?
///\return Retourne true si le Decor bloque le pathing
///
    bool bloquant();
    
private:
    int id;
    bool bloquant_;
    Texture *texture;
};

}
#endif // DECORTEMPLATE_HPP
