#ifndef PAYS_HPP
#define PAYS_HPP

#include <string>
#include <list>


using std::string;
using std::list;

namespace cce{
class Region; 
class PointSpawn;
class Pays
{

public:
Pays(int _income, string _nom, list<Region> _regions, PointSpawn* _ps);
virtual ~Pays();

///
///\brief income du pays
///\return Retourne l'income du pays
///
	    int getIncome();

///
///\brief definit l'income du pays
///\param incom : income à associer
///
	    void setIncome(int incom);

///
///\brief nom du pays
///\return Retourne le nom du pays
///
	    string getNom();
///
///\brief definit le nom du pays
///\param n : nom à associer
///
            void setNom(string n);
	    
///\brief regions du pays
///\return Retourne les regions du pays
///
            list<Region> getRegions();
	    
///
///\brief definit les regions d'un pays
///\param r : regions a associer
///
            void setRegions(list<Region> r);
///	    
///
///\brief point de spawn du pays
///\return Retourne le point de spawn du pays
///
            PointSpawn* getPointSpawn();
///
///\brief definit le point de spawn du pays
///\param ps : point de spawn à associer
///
            void setPointSpawn(PointSpawn* ps);
	    
private : 
	    int income;
	    string nom;
	    list<Region> regions;
	    PointSpawn* ps;	  

};
}
#endif // PAYS_HPP
