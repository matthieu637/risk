#ifndef POINT_HPP
#define POINT_HPP

namespace cce{

class Point
{

public:
  Point();
  Point(int x, int y);
  virtual ~Point();
  
  int getX();
  int getY();
  
private:
  int x, y;
};

}

#endif // POINT_HPP
