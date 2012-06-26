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
}
namespace edt{

class Carte;
  
class GUI;

class PaletteRegions : public cce::Palette
{
public :
  PaletteRegions();
  virtual ~PaletteRegions();
  void init(GUI const *gui, string nom, Carte* c);
  void updateListRegions(list<string> noms);
  bool onNameChange(const CEGUI::EventArgs &e);
  bool onChangeSelection(const CEGUI::EventArgs &e);
  bool onIncomeChange(const CEGUI::EventArgs &e);
  
private :
  CEGUI::Listbox* lbox;
  CEGUI::Editbox* ebox;
  CEGUI::Editbox* eboxinc;
  CEGUI::ListboxItem* lbti;
  Carte* carte;
};
}

#endif // PALETTEREGIONS_HPP
