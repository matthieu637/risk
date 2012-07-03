///
///\file BastonManager.hpp
///\brief Gere les .
///\author Aymeric
///

#ifndef CLI_BASTONMANAGER_H
#define CLI_BASTONMANAGER_H

#include "bib/Singleton.hpp"
#include "cce/UnitTemplate.hpp"
#include <vector>

using std::vector;


namespace cli {

class BastonManager : public bib::Singleton<BastonManager>
{
    friend class bib::Singleton<BastonManager>;

    protected:
      BastonManager();
      virtual ~BastonManager();
	
    public:
      float reduction_degats(cce::defence_type,cce::damage_type);
    
    private:
      ///
      ///\Brief Determine les constantes entre les différents type d'attaque et de défense : coefficients multiplicateurs de défense par rapport à l'attaque
      ///
      vector<vector<float>> taux;

  
};

} /* End of namespace cce */

#endif // CCE_IMAGEMANAGER_H