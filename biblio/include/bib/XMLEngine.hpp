#ifndef XMLENGINE_HPP
#define XMLENGINE_HPP

///
///\file XMLEngine.hpp
///\brief Permet d'enregistrer et de lire des objets serializable
///\author matthieu
///


#include <fstream>
#include <string>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include "test/SampleData.hpp"
#include "bib/Logger.hpp"

using std::ofstream;
using std::ifstream;
using boost::archive::xml_oarchive;
using boost::archive::xml_iarchive;
using boost::serialization::make_nvp;

namespace bib{

class XMLEngine
{
public:
  
///
///\brief Sauvegarder une instance d'objet dans un fichier XML
///
///\param object : objet en question
/// 	    name : nom de l'entrée XML ( le nom de la classe est en générale une bonne idée )
///    file_name : chemin vers le fichier à écrire
///
  template<class T>
  static void save(const T& object, const char* name, const string& file_name){
    LOG_INFO("Enregistrement du fichier XML " << file_name);
    
    ofstream outputFile(file_name);
    xml_oarchive xml(outputFile);
    xml << make_nvp(name, object);
  }

///
///\brief Créer une instance d'objet à partir d'un fichier XML
///
///\param name : nom de l'entrée XML ( le nom de la classe est en générale une bonne idée )
///    file_name : chemin vers le fichier XML à lire
///
  template<class T>
  static T load(const char* name, const string& file_name){
    LOG_INFO("Lecture du fichier XML " << file_name);
    
    T object;
    ifstream inputFile(file_name);
    xml_iarchive xml(inputFile);
    xml >> make_nvp(name, object);
    return object;
  }
};

}

#endif // XMLENGINE_HPP
