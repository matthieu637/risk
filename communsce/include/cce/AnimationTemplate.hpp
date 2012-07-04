#ifndef ANIMATIONTEMPLATE_HPP
#define ANIMATIONTEMPLATE_HPP

#include <string>
#include <boost/serialization/nvp.hpp>
#include <Thor/Animation.hpp>
#include <SFML/Graphics.hpp>

using std::string;
using boost::serialization::make_nvp;

namespace cce {
  class AnimationTemplate
  {
  public:
    AnimationTemplate();
    AnimationTemplate(string n, int num, int deb,int end, float hauteur, float largeur, float tps);
    virtual ~AnimationTemplate();
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        (void) version;
        ar & make_nvp("num_Animation", num_Animation);
	ar & make_nvp("temps",temps);
	ar & make_nvp("rect_hauteur", rect_hauteur);
	ar & make_nvp("rect_largeur", rect_largeur);
	ar & make_nvp("nom", nom);
	ar & make_nvp("debut",debut);
	ar & make_nvp("fin", fin);
    }
    
    string getNom();
    int getNum_Animation();// = l'animation se trouve à quelle ligne
    int getDebut();// on commence à quelle image de la ligne
    int getFin();// on finit à quelle image de la ligne
    float getTemps();
    float getRect_hauteur();
    float getRect_largeur();
    thor::Animator<sf::Sprite, std::string>* getAnimathor();
    
  private:
    float temps,rect_hauteur,rect_largeur;
    string nom;
    int num_Animation,debut,fin;
    thor::Animator<sf::Sprite, std::string> animathor;
  
  
  };
}
#endif // UNITTEMPLATE_HPP