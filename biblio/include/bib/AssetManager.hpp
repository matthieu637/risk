
#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

///
///\file AssetManager.hpp
///\brief Gere les ressources tirées des fichiers, classe abstraite.
///\author Aymeric
///

#include <list>
#include <map>
#include <iostream>
#include <string>
#include "bib/Logger.hpp"

namespace bib {

template <class T>
class AssetManager
{
public:
    AssetManager() : resource_directories_(), assets_()
    {
    }
    virtual ~AssetManager()
    {
    }
public:

    ///
    ///\brief Ajoute un repertoire pour la recherche des fichiers.
    ///\param directory : path du repertoire relatif a l'application
    ///
    void add_resource_directory( const std::string& directory )
    {
        // Cherche si le chemin existe déjà
        for( std::list<std::string>::const_iterator it = resource_directories_.begin();
                it != resource_directories_.end();
                ++it )
        {
            // Si il existe déjà, on l'ignore
            if( directory == (*it) )
                return;
        }

        // Ajoute le repertoire
        LOG_DEBUG("Répertoire " << directory << " ");
        resource_directories_.push_back( directory );
    }

    ///
    ///\brief Supprime un repertoire pour la recherche des fichiers.
    ///\param directory : path du repertoire relatif a l'application
    ///
    void remove_resource_directory( const std::string& directory )
    {
        for( std::list<std::string>::iterator it = resource_directories_.begin();
                it != resource_directories_.end(); )
        {
            // Le chemin est trouvé, on le supprime
            if( directory == (*it) ){
                it = resource_directories_.erase( it );
		LOG_DEBUG("Répertoire " << directory << " ");
	    }
            else
                ++it;
        }
    }

    ///
    ///\brief Charger une ressource depuis un fichier
    ///\param ID: ID du fichier, filename : nom du fichier
    ///
    void load_asset( int ID, const std::string& filename )
    {
        bool succes = false;
        T* asset ;

        // Fouille dans les repertoires
        for( std::list< std::string >::iterator it = resource_directories_.begin();
                it != resource_directories_.end();
                ++it )
        {
            asset = creer_ressource(((*it) + filename ), &succes);
            if( succes )
            {
                assets_.insert( std::pair<int,T*>(ID, asset) );
		LOG_DEBUG("Chargement du fichier " << filename << " avec l'id " << id);
                return;
            }
        }
        LOG_ERROR("Impossible de charger le fichier "<< filename << " ID " << id);
        assets_.insert( std::pair<int,T*>(ID, asset) );
    }

    ///
    ///\brief Obtenir une ressource d'apres son ID
    ///\param filename : nom du fichier
    ///\return la ressource sous forme T
    ///
    T& get_asset( const int ID )
    {
        return *assets_[ID];
    }

    ///
    ///\brief Verifier si une ressource est chargee
    ///\param ID: ID de la ressource
    ///\return un boolean d'existence
    ///
    bool is_loaded( const int ID )
    {
        return assets_.find(ID) != assets_.end();
    }

    ///
    ///\brief Retire la ressource de la memoire
    ///\param asset : asset a supprimer
    ///
    void delete_asset( const T& asset )
    {
        typename std::map<int, T>::iterator it = assets_.begin();
        for( it; it != assets_.end(); ++it)
            if( &asset == &it->second )
                assets_.erase( it );
    }

    ///
    ///\brief Retire l'asset de la memoire
    ///\param id : ID du fichier
    ///
    void delete_asset( const int id )
    {
        assets_.erase( id );
    }

    ///
    ///\brief Renvoie l'iterator de debut et de fin sous forme de pair
    ///
    std::pair <typename std::map<int, T>::iterator, typename std::map<int, T>::iterator> get_iterator()
    {
        return std::pair <typename std::map<int, T>::iterator, typename std::map<int, T>::iterator>
               (assets_.begin(),assets_.end());
    }

protected:
    //Creation de la ressource
    virtual T* creer_ressource(const std::string& path, bool *succes) =0;
    //Collection des repertoires de recherche
    std::list< std::string > resource_directories_;
    //Collection d'assets selon le nom des fichier
    std::map< int, T* > assets_;
};

} /* End of namespace cce */

#endif // ASSETMANAGER_HPP
