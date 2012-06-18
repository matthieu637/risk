#ifndef FLAG_HPP
#define FLAG_HPP

#include "Decor.hpp"
#include "Univers.hpp"
#include "DecorTemplate.hpp"
#include <boost/serialization/nvp.hpp>

using boost::serialization::make_nvp; 

namespace cce{

class Flag : public Decor
{

public:
    Flag(DecorTemplate *_dt, int _x, int _y);
    Flag();
    virtual ~Flag();
    
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
    
private:
  int x;
  int y;
  DecorTemplate* dt;
};

}

#endif // FLAG_HPP
