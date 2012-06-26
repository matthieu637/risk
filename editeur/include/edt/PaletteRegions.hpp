#ifndef PALETTEREGIONS_HPP
#define PALETTEREGIONS_HPP

#include "cce/Palette.hpp"
#include <string>
#include <list>

using std::string;
using std::list;

namespace CEGUI{
  class Listbox;
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
private :
  CEGUI::Listbox* lbox;
  
};
}

#endif // PALETTEREGIONS_HPP
