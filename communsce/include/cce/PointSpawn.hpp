#ifndef POINTSPAWN_HPP
#define POINTSPAWN_HPP

#include "Decor.hpp"
#include "DecorTemplate.hpp"
#include "Univers.hpp"
#include <boost/serialization/nvp.hpp>

using boost::serialization::make_nvp; 

namespace cce{ 
class PointSpawn : public Decor
{

public:
    PointSpawn(DecorTemplate *_dt, int _x, int _y);
    PointSpawn();
    virtual ~PointSpawn();
    
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & make_nvp("x", x); 
	ar & make_nvp("y", y);
	boost::serialization::split_member(ar, *this, version);
    }

    template<class Archive>
    void save(Archive& ar, const unsigned int version) const {
        (void) version;
        (void) ar;
        int id = -1;
        if(dt != nullptr)
            id = dt->getID();
        ar << make_nvp("id", id);

    }

    template<class Archive>
    void load( Archive & ar, const unsigned int file_version ) {
        (void) file_version;
        (void) ar;
        int id;
        ar >> make_nvp("id", id);
        
	if(id != -1 )
	  dt=(Univers::getInstance()->getDecorTemplate(id));
    }
    
private :
  DecorTemplate* dt;
  int x;
  int y;
};

}

#endif // POINTSPAWN_HPP
