#include "../../include/cce/Tile.hpp"

namespace cce{

Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::init(TileTemplate *_tt, int _x, int _y)
{
    setTemplate(_tt);
    setCoordonnes(_x,_y);
}

TileTemplate* Tile::getTemplate() const
{
    return tt;
}

void Tile::setTemplate(TileTemplate *_tt)
{
    tt = _tt;
    setTexture(*tt->getTexture());
}

void Tile::unsetTemplate()
{
    tt = nullptr;
    //setTexture(nullptr);
}

void Tile::setCoordonnes(const int x_rect, const int y_rect)
{
    y = y_rect;
    x = x_rect;
    //retire un peu de hauteur pour les tiles qui dépasse la hauteur conforme ( brins d'herbe , ...)
    y -= tt->getDecalageHauteur();

#ifndef NDEBUG
    //std::cout << "read id : " << _id << " x : " << x<< " y : " << y << "\t\t";
    //std::cout << "write coord x : " << GetPosition().x << " y : " << GetPosition().y << std::endl;
#endif

}

}