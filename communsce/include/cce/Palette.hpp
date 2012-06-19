#ifndef PALETTE_HPP
#define PALETTE_HPP
#include <CEGUI/CEGUI.h>
#include <string>

namespace cce{
  
class GUI;

class Palette
{

public:
  Palette();
  virtual ~Palette();
  void init(const GUI* gui, const std::string& conteneur);

private:
  CEGUI::FrameWindow* fenetre;
};

}

#endif // PALETTE_HPP
