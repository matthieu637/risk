#include "cli/BastonManager.hpp"

namespace cli{
  
BastonManager::BastonManager(){
   taux = {
	///défense tough
	{
	0.5,
	0.9,
	0.9,
	0.9
	},
	///défense reflexion
	{
	0.9,
	0.5,
	0.9,
	0.9
	},
	///défense shield
	{
	0.9,
	0.9,
	0.5,
	0.9
	},
	///défense massive
	{
	0.9,
	0.9,
	0.9,
	0.5
	},
	
      };
}

  
BastonManager::~BastonManager(){
  
}
float BastonManager::reduction_degats(cce::defence_type def,cce::damage_type dmg){
    return taux[def][dmg];
}
}