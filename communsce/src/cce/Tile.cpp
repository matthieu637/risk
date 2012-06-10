#include "cce/Tile.hpp"
#include "cce/TileTemplate.hpp"

namespace cce{

Tile::Tile()
{

}

Tile::~Tile()
{

}

void Tile::init(TileTemplate *_tt, int x, int y)
{
    setTemplate(_tt);
    setPosition(x,y);
}

TileTemplate* Tile::getTemplate() const
{
    return tt;
}

void Tile::setTemplate(TileTemplate *_tt)
{
    move(0, -tt->getDecalageHauteur());
    tt = _tt;
    setTexture(*tt->getTexture());
    move(0, tt->getDecalageHauteur());
}

void Tile::unsetTemplate()
{
    tt = nullptr;
    //setTexture(nullptr);
}

void Tile::setPosition(float x, float y)
{
    Sprite::setPosition(x, y);
    //retire un peu de hauteur pour les tiles qui dépasse la hauteur conforme ( brins d'herbe , ...)
    move(0, tt->getDecalageHauteur());

}

}