
#Debug / Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

#Variable cmake non utilisé
set(CMAKE_INSTALL_PREFIX "" CACHE PATH "Variable non utilisé" FORCE)

if(WINDOWS)
	#Enleve le projet ZERO_CHECK de l'IDE MSV
	set(CMAKE_SUPPRESS_REGENERATION TRUE)
	
	#Linker ou non la librarie sfml-main dans windows
	set(LINK_SFML_MAIN FALSE CACHE BOOL "Linker la bibliothèque main?")
endif()

#Type de la bibliothèque de sortie
set(TYPE_LIB STATIQUE CACHE STRING "Choisir le type la bibliothèque (STATIQUE ou DYNAMIQUE)")

#Dossier CommunsCE
set(BIBLIO_PATH "${CMAKE_SOURCE_DIR}/../Biblio" CACHE PATH "Chemin vers la librarie Bibliothèque")

## Option de compilation pour g++
if(CMAKE_COMPILER_IS_GNUCXX)
    if(${CMAKE_BUILD_TYPE} MATCHES Release)
      set(CMAKE_CXX_FLAGS "-O2")        ## Optimisation
      set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
    else()
      set(CMAKE_CXX_FLAGS "-g -DDEBUG -Wall -pedantic -Wextra -ansi -std=c++0x")
    endif()
endif()
