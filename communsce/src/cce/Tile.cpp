#include "cce/Tile.hpp"
#include "cce/TileTemplate.hpp"

namespace cce {

    Tile::Tile():tt(nullptr) {

    } Tile::~Tile() {

    }

    void Tile::init(int x, int y) {
	this->setPosition(x, y);
    }

    TileTemplate *Tile::getTemplate() const {
	return tt;
    } void Tile::setTemplate(TileTemplate * _tt) {
	tt = _tt;
	setTexture(*(tt->getTexture()), true);
    }

    void Tile::unsetTemplate() {
	tt = nullptr;
	// TODO Essayer de trouver une fonctione qui supprime la texture au lieu de dessier un rectangle de largeur 0
	setTextureRect(sf::IntRect(0, 0, 0, 0));
    }

    void Tile::setPosition(float x, float y) {
	Sprite::setPosition(x, y);
	//retire un peu de hauteur pour les tiles qui dépasse la hauteur conforme ( brins d'herbe , ...)
	if (tt != nullptr)
	    move(0, -tt->getDecalageHauteur());
    }

}