#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "cce/Point.hpp"
#include <deque>
#include <boost/serialization/deque.hpp>
#include <Thor/Multimedia/ConcaveShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <bib/Logger.hpp>

using std::deque;
using boost::serialization::make_nvp;

namespace cce{

class Polygon : public thor::ConcaveShape
{

public:
  Polygon();
  Polygon(const sf::ConvexShape& ch);
  virtual ~Polygon();
  
  void addPoint(Point p);

  bool contient(Point p);
  
  void removeLastPoint();
  
  virtual void setPoint(unsigned int index, const sf::Vector2f& point);
  
      template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void)version;
        ar & make_nvp("Points", points); 
	boost::serialization::split_member(ar, *this, version);
    }
    
    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        (void) version;
        (void) ar;
    }

    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
        (void) file_version;
        (void) ar;

	this->
	setPointCount(points.size());
	deque<Point>::iterator it;
	unsigned int i=0;
	for(it=points.begin();it != points.end(); it++){
	  setPoint(i, sf::Vector2f(it->getX(), it->getY()));
	  i++;
	}
	setFillColor(sf::Color(100,100,100,100));
	setOutlineColor(sf::Color::Red);
	setOutlineThickness(3.);
    }
  
private:
  deque<Point> points;
};

}

#endif // POLYGON_HPP
