#ifndef PALETTEREGIONS_HPP
#define PALETTEREGIONS_HPP

#include "edt/Palette.hpp"
#include <string.h>

using std::string;

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
  void updateListRegions(string noms);
private :
  CEGUI::Listbox* lbox;
  
};
}

#endif // PALETTEREGIONS_HPP
