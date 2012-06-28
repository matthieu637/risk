#include "cce/UnitTemplate.hpp"
#include "cce/ImageManager.hpp"

namespace cce {

UnitTemplate::UnitTemplate()
{
//     dmg_min = 10;
//     dmg_max = 100;
//     defence = 40;
//     move_speed = 100;
//     attack_speed = 100;
//     nom="WOL";
//     description = "Wake On Lan, ç é ?";
//     collision_ = true;
//     dmg_type = laser;
//     def_type = acier;
}

void UnitTemplate::loadAfterXML(int id)
{
    this->id = id;
    
    //à supprimer pour ne pas charger toutes les textures des unités en mémoire
    ImageManager::getInstance()->load_asset(id, path);
    texture = &ImageManager::getInstance()->get_asset(id);
}

UnitTemplate::~UnitTemplate()
{

}

void UnitTemplate::setDamage(int dmg_min, int dmg_max) {
    this->dmg_min = dmg_min;
    this->dmg_max = dmg_max;
}

void UnitTemplate::setDefence(int defence) {
    this->defence = defence;
}

void UnitTemplate::setDescription(string description) {
    this->description = description;
}

void UnitTemplate::setMoveSpeed(int move_speed) {
    this->move_speed = move_speed;
}

void UnitTemplate::setAttackSpeed(int attack_speed) {
    this->attack_speed = attack_speed;
}

void UnitTemplate::setCollision(bool collision) {
    this->collision_ = collision;
}

void UnitTemplate::setDamageType(damage_type dmg_type) {
    this->dmg_type = dmg_type;
}

void UnitTemplate::setDefenseType(defence_type def_type) {
    this->def_type = def_type;
}

int UnitTemplate::getID() {
    return id;
}
string UnitTemplate::getNom() {
    return nom;
}
string UnitTemplate::getDescription() {
    return description;
}
bool UnitTemplate::collision() {
    return collision_;
}
int UnitTemplate::getDamageMin() {
    return dmg_min;
}
int UnitTemplate::getDamageMax() {
    return dmg_max;
}
int UnitTemplate::getDefence() {
    return defence;
}
damage_type UnitTemplate::getDamageType() {
    return dmg_type;
}
defence_type UnitTemplate::getDefenseType() {
    return def_type;
}
float UnitTemplate::getAttackSpeed() {
    return attack_speed;
}
int UnitTemplate::getMoveSpeed() {
    return move_speed;
}
Texture* UnitTemplate::getTexture()
{
  return texture;
}

}
