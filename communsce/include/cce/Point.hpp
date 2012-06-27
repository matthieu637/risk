#ifndef POINT_HPP
#define POINT_HPP

#include <boost/serialization/nvp.hpp>

using boost::serialization::make_nvp;

namespace cce {

class Point
{

public:
    Point();
    Point(int x, int y);
    virtual ~Point();

    int getX();
    int getY();

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void)version;
        ar & make_nvp("x", x);
        ar & make_nvp("y", y);
    }

private:
    int x, y;
};

}

#endif // POINT_HPP
