#ifndef PALETTE_HPP
#define PALETTE_HPP
#include <CEGUI/CEGUI.h>
#include <string>

using std::string;

namespace cce{
  
class GUI;

class Palette
{

public:
  Palette();
  virtual ~Palette();

  void init(const GUI* gui, string nom);
  void hide();
  bool onClose(const CEGUI::EventArgs&);

protected:
  CEGUI::FrameWindow* fenetre;
};

}

#endif // PALETTE_HPP
