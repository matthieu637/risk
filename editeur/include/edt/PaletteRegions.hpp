
#ifndef PALETTEREGIONS_HPP
#define PALETTEREGIONS_HPP

#include "cce/Palette.hpp"
#include <string>
#include <list>

using std::string;
using std::list;

namespace CEGUI{
  class Listbox;
  class Editbox;
  class ListboxItem;
  class Checkbox;
  class Combobox;
}
namespace edt{

class Region;

class Modele;
  
class GUI;

class PaletteRegions : public cce::Palette
{
public :
  PaletteRegions();
  virtual ~PaletteRegions();
  void init(GUI const *gui, string nom, Modele* m);
  void updateListRegions(list<string> noms);
  bool onRegionNameChange(const CEGUI::EventArgs &e);
  bool onCheckedChange(const CEGUI::EventArgs &e);
  bool onChangeSelection(const CEGUI::EventArgs &e);
  bool onIncomeChange(const CEGUI::EventArgs &e);
  bool onResetPoly(const CEGUI::EventArgs &e);
  bool onDefinirPoly(const CEGUI::EventArgs &e);
  bool onComboboxSelectionChange(const CEGUI::EventArgs &e);
  bool onShow(const CEGUI::EventArgs &e);
  
  
private :
  void hideAllPoly();
  void showAllPoly();
  void reloadPaysBox();
  
  CEGUI::Listbox* lbox;
  CEGUI::Editbox* ebox;
  CEGUI::Editbox* eboxinc;

  CEGUI::PushButton* resetPoly;
  CEGUI::PushButton* addPoint;
  CEGUI::Checkbox* cboxpoly;
  CEGUI::Combobox* comboBoxPays;
  string ancien;
  
  Modele* modele;
  Region* current_reg;
};
}

#endif // PALETTEREGIONS_HPP
