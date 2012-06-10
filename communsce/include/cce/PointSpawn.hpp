#ifndef POINTSPAWN_HPP
#define POINTSPAWN_HPP

#include "Decor.hpp"

namespace cce{

class PointSpawn : public Decor
{

public:
    PointSpawn(DecorTemplate *_dt, int _x, int _y);
    virtual ~PointSpawn();
};

}

#endif // POINTSPAWN_HPP
