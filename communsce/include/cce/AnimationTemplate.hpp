#ifndef ANIMATIONTEMPLATE_HPP
#define ANIMATIONTEMPLATE_HPP

#include <string>
#include <boost/serialization/nvp.hpp>

using std::string;
using boost::serialization::make_nvp;

namespace cce {
  class AnimationTemplate
  {
  public:
    AnimationTemplate();
    virtual ~AnimationTemplate();
    
    void loadAfterXML(int _id);
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
        ar & make_nvp("num_Animation", num_Animation);
	ar & make_nvp("temps",temps);
	ar & make_nvp("rect_hauteur", rect_hauteur);
	ar & make_nvp("rect_largeur", rect_largeur);
	ar & make_nvp("nom", nom);
    }
    
    string getNom();
    int getNum_Animation();// = l'animation se trouve à quelle ligne
    float getTemps();
    float getRect_hauteur();
    float getRect_largeur();
    
  private:
    float temps,rect_hauteur,rect_largeur;
    string nom;
    int num_Animation;
  
  
  };
}
#endif // UNITTEMPLATE_HPP