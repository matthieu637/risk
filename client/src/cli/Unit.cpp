#include "cli/Unit.hpp"


namespace cli {

  Unit::Unit()
  {

  }
  
  void Unit::setUnitTemplate(cce::UnitTemplate *ut){
	unitTemplate = ut;//met a jour les caractéristiques de l'unité
	setTexture(ut->getTexture());//met a jour l'image de l'unité
	
  }
  
  void Unit::setId(int id){
      setUnitTemplate(cce::Univers::getInstance()->getUnitTemplate(id));
  }

}