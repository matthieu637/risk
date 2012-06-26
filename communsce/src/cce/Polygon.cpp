#include "cce/Polygon.hpp"
#include "cce/Point.hpp"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

namespace cce{

Polygon::Polygon()
{
  
}

Polygon::~Polygon()
{
  
}

void Polygon::addPoint(Point p)
{
    points.push_back(p);
}

bool Polygon::contient(Point p)
{
  int counter = 0;
  unsigned int i;
  double xinters;
  Point p1,p2;

  p1 = points[0];
  for (i = 1;i < points.size();i++) {
    p2 = points[i % points.size()];
    if (p.getY() > MIN(p1.getY(),p2.getY())) {
      if (p.getY() <= MAX(p1.getY(),p2.getY())) {
        if (p.getX() <= MAX(p1.getX(),p2.getX())) {
          if (p1.getY() != p2.getY()) {
            xinters = (p.getY()-p1.getY())*(p2.getX()-p1.getX())/(p2.getY()-p1.getY())+p1.getX();
            if (p1.getX() == p2.getX() || p.getX() <= xinters)
              counter++;
          }
        }
      }
    }
    p1 = p2;
  }

  if (counter % 2 == 0)
    return(false);
  else
    return(true);
}

}