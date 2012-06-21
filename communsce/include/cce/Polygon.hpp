#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "cce/Point.hpp"
#include <vector>

using std::vector;

namespace cce{

class Polygon
{

public:
  Polygon();
  virtual ~Polygon();
  
  void addPoint(Point p);

  bool contient(Point p);
  
private:
  vector<Point> points;
};

}

#endif // POLYGON_HPP
