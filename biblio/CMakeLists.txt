cmake_minimum_required(VERSION 2.8)

#Nom du projet
project(Biblio CXX)

#Détection de l'OS
include(${CMAKE_SOURCE_DIR}/cmake/OS.cmake)

#Définition des variables globales
include(${CMAKE_SOURCE_DIR}/cmake/Variables.cmake)

#Trouve Boost
find_package(Boost)

#Include
include_directories(${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS} )

#Source & headers
file ( GLOB_RECURSE sources src/*.cpp include/*.hpp)

#### Création de la librarie ####

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

if(TYPE_LIB MATCHES DYNAMIQUE)
  add_library(biblio SHARED ${sources})
else()
  add_library(biblio STATIC ${sources})
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set_target_properties(biblio PROPERTIES DEBUG_POSTFIX -d)
endif()

