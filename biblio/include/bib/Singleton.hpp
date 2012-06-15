#ifndef SINGLETON_HPP
#define SINGLETON_HPP

///
///\file Singleton.hpp
///\brief Template de base pour le pattern singleton
///\author matthieu
///
///
/// \example Pour l'utiliser il suffit de faire hériter la classe par celle-ci
///          et d'ajouter : friend class bib::Singleton<MaClasse>;
///
///


#include <assert.h>

namespace bib {

template <class T>
class Singleton
{


public:
///
///\brief Méthode statique et public pour récupérer l'instance du singleton
///
    static T* getInstance()
    {
        assert(_singleton != nullptr);
        return _singleton;
    }
///
///\brief Constructeur privée/protected pour empécher l'instanciation n'importe où
///
protected:
    Singleton() {}
    ~Singleton() {}

private:
    static T* _singleton;
};

template <class T>
T *Singleton<T>::_singleton = new T;

}

#endif