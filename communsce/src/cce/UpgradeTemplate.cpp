#include "cce/UpgradeTemplate.hpp"

namespace cce {

UpgradeTemplate::UpgradeTemplate()
{

}

void UpgradeTemplate::init(int id, string nom)
{
    this->id = id;
    this->nom = nom;
}

UpgradeTemplate::~UpgradeTemplate()
{

}

void UpgradeTemplate::setDescription(string description) {
    this->description = description;
}
int UpgradeTemplate::getID() {
    return id;
}
string UpgradeTemplate::getNom() {
    return nom;
}
string UpgradeTemplate::getDescription() {
    return description;
}

}
