#ifndef PALETTEREGIONS_HPP
#define PALETTEREGIONS_HPP

#include "edt/Palette.hpp"
#include <string>
#include <list>

using std::string;
using std::list;

namespace CEGUI{
  class Listbox;
}
namespace edt{

class PaletteRegions : public Palette
{
public :
  PaletteRegions();
  virtual ~PaletteRegions();
  void init(GUI const *gui, string nom);
  void updateListRegions(list<string> noms);
private :
  CEGUI::Listbox* lbox;
  
};
}

#endif // PALETTEREGIONS_HPP
