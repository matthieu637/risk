#ifndef PALETTEINFORMATIONSELECTION_HPP
#define PALETTEINFORMATIONSELECTION_HPP

#include "cce/Palette.hpp"
#include "cce/Decor.hpp"
#include <string>

using std::string;

namespace edt{

class Controleur;
class Modele;
class GUI;

class PaletteInformationSelection : public cce::Palette
{
  
public :
  PaletteInformationSelection();
  virtual ~PaletteInformationSelection();
  void init(GUI const *gui, string nom, Controleur* c, Modele* m);
  void setCurrentSelection(cce::Decor* d);
  void update();
  bool onTailleSocleChange(const CEGUI::EventArgs &e);
  
private :
  //modele controleur
  Controleur* control;
  Modele* modele;
  cce::Decor* current_selection;
  
  //objets de l'interface graphique
  CEGUI::Editbox* socle_taille;
  
};

}

#endif // PALETTEPAYS_HPP
