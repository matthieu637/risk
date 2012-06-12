#include "cce/Tile.hpp"
#include "cce/TileTemplate.hpp"

namespace cce{

Tile::Tile():tt(nullptr)
{

}

Tile::~Tile()
{

}

void Tile::init(int x, int y)
{
    setPosition(x,y);
}

TileTemplate* Tile::getTemplate() const
{
    return tt;
}

void Tile::setTemplate(TileTemplate *_tt)
{
    tt = _tt;
    setTexture(*(tt->getTexture()));
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
    move(0, - tt->getDecalageHauteur());
}

}