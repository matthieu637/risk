#ifndef PALETTE_HPP
#define PALETTE_HPP
#include <CEGUI/CEGUI.h>
#include <string.h>

using std::string;
namespace edt{
  
class GUI;

class Palette
{

public:
  Palette();
  virtual ~Palette();
  void init(const GUI* gui, string nom);

protected:
  CEGUI::FrameWindow* fenetre;
};

}

#endif // PALETTE_HPP
