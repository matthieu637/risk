#ifndef PALETTE_HPP
#define PALETTE_HPP
#include <CEGUI/CEGUI.h>

namespace edt{
  
class GUI;

class Palette
{

public:
  Palette();
  virtual ~Palette();
  void init(const GUI* gui);

private:
  CEGUI::FrameWindow* fenetre;
};

}

#endif // PALETTE_HPP
