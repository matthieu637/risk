#ifndef SAMPLEDATA_HPP
#define SAMPLEDATA_HPP

///
///\file SampleData.hpp
///\brief Example d'une classe serializable avec des conteneurs std
///\author matthieu
///

#include <list>
#include <string>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>

using std::list;
using std::string;
using boost::serialization::make_nvp;

class SampleData
{

public:
///
///\brief Constructeur sans arguments à définir obligatoirement pour 
///	  permettre au XMLEngine de créer un objet vide avant de le remplir
///
    SampleData(){
    }

///
///\brief Constructeur sans arguments, obligatoire pour créer un objet vide
///
    SampleData(string d1, string d2, bool hotties, int id):hot(hotties), id(id){
      meat.push_back(d1);
      meat.push_back(d2);
    }

///
///\brief Getters banales
///
    list<string> getMeat(){
	return meat;
    }
    
    int getID(){
      return id;
    }
    
///
///\brief Méthode à définir obligatoirement pour la serialization
///       BOOST_SERIALIZATION_NVP(id) <=> make_nvp("id", hot);
///
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        (void) version;
        ar & BOOST_SERIALIZATION_NVP(id);
        ar & make_nvp("Srly", hot);
        ar & make_nvp("Hotties", meat);
    }
    
private:
   list<string> meat;
   bool hot;
   int id;
};

#endif // SAMPLEDATA_H
