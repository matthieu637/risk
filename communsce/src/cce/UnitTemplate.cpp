#include "../../include/cce/UnitTemplate.hpp"

namespace cce{

UnitTemplate::UnitTemplate()
{
  
}

void UnitTemplate::init(int id, string nom, bool collision)
{
  this->id = id;
  this->nom = nom;
  this->collision_ = collision;
}

UnitTemplate::~UnitTemplate()
{

}

void UnitTemplate::setDamage(int dmg_min, int dmg_max){
  this->dmg_min = dmg_min;
  this->dmg_max = dmg_max;
}
    
void UnitTemplate::setDefence(int defence){
  this->defence = defence;
}
    
void UnitTemplate::setDescription(string description){
  this->description = description;
}
    
void UnitTemplate::setMoveSpeed(int move_speed){
  this->move_speed = move_speed;
}
    
void UnitTemplate::setAttackSpeed(float attack_speed){
  this->attack_speed = attack_speed;
}
    
void UnitTemplate::setCollision(bool collision){
  this->collision_ = collision;
}
    
void UnitTemplate::setDamageType(damage_type dmg_type){
  this->dmg_type = dmg_type;
}
    
void UnitTemplate::setDefenseType(defence_type def_type){
  this->def_type = def_type;
}

int UnitTemplate::getID(){
  return id;
}
string UnitTemplate::getNom(){
  return nom;
}
string UnitTemplate::getDescription(){
  return description;
}
bool UnitTemplate::collision(){
  return collision_;
}
int UnitTemplate::getDamageMin(){
  return dmg_min;
}
int UnitTemplate::getDamageMax(){
  return dmg_max;
}
int UnitTemplate::getDefence(){
  return defence;
}
damage_type UnitTemplate::getDamageType(){
  return dmg_type;
}
defence_type UnitTemplate::getDefenseType(){
  return def_type;
}
float UnitTemplate::getAttackSpeed(){
  return attack_speed;
}
int UnitTemplate::getMoveSpeed(){
  return move_speed;
}

}