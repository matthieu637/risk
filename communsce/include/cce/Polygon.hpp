#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "cce/Point.hpp"
#include <deque>
#include <boost/serialization/deque.hpp>

using std::deque;
using boost::serialization::make_nvp;

namespace cce{

class Polygon
{

public:
  Polygon();
  virtual ~Polygon();
  
  void addPoint(Point p);

  bool contient(Point p);
  
      template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void)version;
        ar & make_nvp("Points", points);    
    }
  
private:
  deque<Point> points;
};

}

#endif // POLYGON_HPP
