#include "cce/Point.hpp"

namespace cce{

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point::Point()
{

}

Point::~Point()
{

}

int Point::getX(){
  return x;
}

int Point::getY(){
  return y;
}

}