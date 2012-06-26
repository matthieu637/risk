cmake_minimum_required(VERSION 2.8)

#Nom du projet
project(Biblio CXX)

#Détection de l'OS
include(${CMAKE_SOURCE_DIR}/cmake/OS.cmake)

#Définition des variables globales
include(${CMAKE_SOURCE_DIR}/cmake/Variables.cmake)

#Trouve Boost
find_package(Boost COMPONENTS serialization)

#Include
include_directories(${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS} )

#Source & headers
file ( GLOB_RECURSE sources_lib src/bib/*.cpp include/bib/*.hpp)
file ( GLOB_RECURSE sources_tests src/*.cpp include/*.hpp)

#### Création de la librarie ####

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

if(TYPE_LIB MATCHES DYNAMIQUE)
  add_library(biblio SHARED ${sources_lib})
else()
  add_library(biblio STATIC ${sources_lib})
endif()

target_link_libraries(biblio ${Boost_LIBRARIES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set_target_properties(biblio PROPERTIES DEBUG_POSTFIX -d)
endif()


add_executable(biblio_test ${sources_tests})
target_link_libraries(biblio_test ${Boost_LIBRARIES})
