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
    for(int i=0; i < ch.getPointCount(); i++)
        points.push_back(cce::Point(ch.getPoint(i).x, ch.getPoint(i).y));

}

Polygon::~Polygon()
{

}

void Polygon::addPoint(Point p)
{   /* Only work with sf::ConvexShape
       points.push_back(p);
       int nb = getPointCount();
       setPointCount(nb+1);
       setPoint(nb, sf::Vector2f(p.getX(), p.getY()));*/
}

bool Polygon::contient(Point p)
{
    int counter = 0;
    unsigned int i;
    double xinters;
    Point p1,p2;

    points.push_back(points[0]);
    
    p1 = points[0];
    for (i = 1; i < points.size(); i++) {
        p2 = points[i % points.size()];
        if (p.getY() > MIN(p1.getY(),p2.getY())) {
            if (p.getY() <= MAX(p1.getY(),p2.getY())) {
                if (p.getX() <= MAX(p1.getX(),p2.getX())) {
                    if (p1.getY() != p2.getY()) {
                        xinters = (double)(p.getY()-p1.getY())*(p2.getX()-p1.getX())/(p2.getY()-p1.getY())+p1.getX();
                        if (p1.getX() == p2.getX() || p.getX() <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }
    
    points.pop_back();

    if (counter % 2 == 0)
        return(false);
    else
        return(true);
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
