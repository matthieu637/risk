#ifndef PAYS_HPP
#define PAYS_HPP

#include <string>
#include <list>


using std::string;
using std::list;

namespace edt{
class Region; 
class PointSpawn; 
class Pays
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
	    
template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
         // à compléter ici
    }
	    
private : 
	    int income;
	    string nom;
	    list<Region> regions;
	    PointSpawn* ps;	  
	    	    	    
};
}
#endif // PAYS_HPP
