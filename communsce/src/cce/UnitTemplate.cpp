#include "cce/UnitTemplate.hpp"
#include "cce/ImageManager.hpp"
#include "bib/Logger.hpp"

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

 mapAnimTemplate["moveUp"] = AnimationTemplate("moveUp",0,0,6,64,47,1);
 mapAnimTemplate["moveRight"] = AnimationTemplate("moveRight",1,0,6,64,47,2);
 mapAnimTemplate["moveDown"] = AnimationTemplate("moveDown",2,0,6,64,47,1.5);
 mapAnimTemplate["moveLeft"] = AnimationTemplate("moveLeft",3,0,6,64,47,0.5);
}

// AnimationTemplate *UnitTemplate::getMapTemplate(){
//     return &mapAnimTemplate["moveLeft"];
// }

map<std::string,AnimationTemplate> *UnitTemplate::getMapTemplate(){
    return &mapAnimTemplate;
}

void UnitTemplate::loadAfterXML(int id)
{
    this->id = id;
    
    //à supprimer pour ne pas charger toutes les textures des unités en mémoire
    ImageManager::getInstance()->load_asset(id, path);
    texture = &ImageManager::getInstance()->get_asset(id);
    initAnimation();
}

UnitTemplate::~UnitTemplate()
{

}

 void UnitTemplate::initAnimation()
{
   // Specify static subrect which is shown unless an other animation is active
  thor::FrameAnimation defaultAnim;
  defaultAnim.addFrame(1.f, sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
  (*getMapTemplate())["moveUp"].getAnimathor()->setDefaultAnimation(defaultAnim, sf::seconds(1.f));
  (*getMapTemplate())["moveRight"].getAnimathor()->setDefaultAnimation(defaultAnim, sf::seconds(1.f));
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

int UnitTemplate::getRange()
{
    return range;
}

int UnitTemplate::getHP()
{
    return hp_max;
}

}

