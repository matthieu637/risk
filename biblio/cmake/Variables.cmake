
#Debug / Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

#Variable cmake non utilisé
set(CMAKE_INSTALL_PREFIX "" CACHE PATH "Variable non utilisé" FORCE)

if(WINDOWS)
	#Enleve le projet ZERO_CHECK de l'IDE MSV
	set(CMAKE_SUPPRESS_REGENERATION TRUE)
endif()

#Type de la bibliothèque de sortie
set(TYPE_LIB STATIQUE CACHE STRING "Choisir le type la bibliothèque (STATIQUE ou DYNAMIQUE)")

## Option de compilation pour g++
if(CMAKE_COMPILER_IS_GNUCXX)
    if(${CMAKE_BUILD_TYPE} MATCHES Release)
      set(CMAKE_CXX_FLAGS "-O2")        ## Optimisation
      set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
    else()
     set(CMAKE_CXX_FLAGS "-g -DDEBUG -Wall -pedantic -Wextra -ansi -std=c++0x")
    endif()
endif()
