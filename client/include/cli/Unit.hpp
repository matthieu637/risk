#ifndef UNIT_HPP
#define UNIT_HPP
#include <cce/Decor.hpp>
#include <cce/UnitTemplate.hpp>
#include <cce/Animation.hpp>

namespace cli{
  class Unit : public cce::Decor
  {
    public:
      Unit();
      void setUnitTemplate(cce::UnitTemplate *ut);
      void setId(int id);
    
    private :
	cce::UnitTemplate *unitTemplate;
	cce::Animation anim;
  };

}
#endif // UNIT_HPP