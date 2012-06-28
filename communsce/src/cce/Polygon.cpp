#include "cce/Polygon.hpp"
#include "cce/Point.hpp"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

namespace cce {

Polygon::Polygon()
{

}

Polygon::Polygon(const sf::ConvexShape& ch) : thor::ConcaveShape(ch)
{
    for(int i=0;i < ch.getPointCount();i++)
      points.push_back(cce::Point(ch.getPoint(i).x, ch.getPoint(i).y));
      
}

Polygon::~Polygon()
{

}

void Polygon::addPoint(Point p)
{/* Only work with sf::ConvexShape
    points.push_back(p);
    int nb = getPointCount();
    setPointCount(nb+1);
    setPoint(nb, sf::Vector2f(p.getX(), p.getY()));*/
}

bool Polygon::contient(Point p)
{
    int j = points.size() - 1;
    int y = p.getY();
    int x = p.getX();
    bool oddNodes = false;

    for(unsigned int i=0; i< points.size(); i++)
        if( (points[i].getY() < y && points[j].getY() >= y
                || points[j].getY() < y && points[i].getY() >= y)
                && (points[i].getX() <= x || points[j].getX() <= x))
        {
            oddNodes ^= ((double)points[i].getX() + (double)(y - points[i].getY())/(points[j].getY() - points[i].getY())*(points[j].getX() - points[i].getX()) < (double)x);
            j=i;
        }
    return oddNodes;
}

void Polygon::removeLastPoint()
{
    points.pop_back();
    setPointCount(getPointCount() - 1);
}

void Polygon::setPoint(unsigned int index, const sf::Vector2f& pp)
{
    thor::ConcaveShape::setPoint(index, pp);
    points[index]=Point(pp.x, pp.y);
}

}
