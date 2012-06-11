cmake_minimum_required(VERSION 2.8)

#Nom du projet
project(CommunsCE CXX)

#Localisation des Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#Détection de l'OS
include(${CMAKE_SOURCE_DIR}/cmake/OS.cmake)

#Définition des variables globales
include(${CMAKE_SOURCE_DIR}/cmake/Variables.cmake)

#Trouver Biblio
find_package(Biblio REQUIRED)

#Trouve Boost
find_package(Boost COMPONENTS serialization)

#Trouver SFML
find_package(SFML 2.0 COMPONENTS system REQUIRED)
find_package(SFML 2.0 COMPONENTS graphics REQUIRED)

#Include
include_directories(${CMAKE_SOURCE_DIR}/include ${SFML_INCLUDE_DIRS} ${BIBLIO_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${THOR_INCLUDE_DIR})

#Source & headers
file ( GLOB_RECURSE sources src/*.cpp include/*.hpp)

#### Création de la librarie ####

set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib")

if(TYPE_LIB MATCHES DYNAMIQUE)
  add_library(communsCE SHARED ${sources})
else()
  add_library(communsCE STATIC ${sources})
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set_target_properties(communsCE PROPERTIES DEBUG_POSTFIX -d)
endif()

#Linker
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LINK_LIB ${SFML_SYSTEM_LIBRARY_DEBUG} ${SFML_GRAPHICS_LIBRARY_DEBUG} ${Boost_LIBRARIES} ${THOR_LIBRARY_DEBUG})
else()
	set(LINK_LIB ${SFML_SYSTEM_LIBRARY_RELEASE} ${SFML_GRAPHICS_LIBRARY_RELEASE} ${Boost_LIBRARIES} ${THOR_LIBRARY_RELEASE})
endif()

#link-main pour windows
if(WINDOWS AND LINK_SFML_MAIN)
	if(CMAKE_BUILD_TYPE MATCHES Debug)
		set(LINK_LIB ${LINK_LIB} ${SFML_MAIN_LIBRARY_DEBUG})
	else()
		set(LINK_LIB ${LINK_LIB} ${SFML_MAIN_LIBRARY_RELEASE})
	endif()
endif()

target_link_libraries(communsCE ${LINK_LIB})
