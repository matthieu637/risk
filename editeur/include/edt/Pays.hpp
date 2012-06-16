#ifndef PAYS_HPP
#define PAYS_HPP

#include <string>
#include <list>
#include <cce/Pays.hpp>


using std::string;
using std::list;
namespace cce{
  class Region; 
  class PointSpawn;
}

using cce::Region;
using cce::PointSpawn;

namespace edt{
 
class Pays : public cce::Pays
{
public : 
Pays(int _income, string _nom, list<Region> _regions, PointSpawn* _ps);
virtual ~Pays();

///
///\brief definit l'income du pays
///\param incom : income à associer
///
	    void setIncome(int incom);

///
///\brief definit le nom du pays
///\param n : nom à associer
///
            void setNom(string n);
	    
///
///\brief definit les regions d'un pays
///\param r : regions a associer
///
            void addRegions(list<Region> r);  
	    
///
///\brief definit le point de spawn du pays
///\param ps : point de spawn à associer
///
            void setPointSpawn(PointSpawn* ps);
	    
	    	  	    	    	    
};
}
#endif // PAYS_HPP
