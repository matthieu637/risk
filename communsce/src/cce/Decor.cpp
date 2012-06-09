#include "../../include/cce/Decor.hpp"

namespace cce{

Decor::Decor(DecorTemplate *_dt, int _x, int _y)
{
    dt = _dt;
    setCoordonnees(_x,_y);
}

Decor::~Decor()
{
    
}

DecorTemplate* Decor::getTemplate() const
{
  return dt;
}

void Decor::setCoordonnees(const int _x, const int _y)
{
  x = _x;
  y = _y;
}

}