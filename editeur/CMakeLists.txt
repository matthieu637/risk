cmake_minimum_required(VERSION 2.8)

#Nom du projet
project(Editeur CXX)

#Localisation des Modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


#Détection de l'OS
include(${CMAKE_SOURCE_DIR}/cmake/OS.cmake)

#Définition des variables globales
include(${CMAKE_SOURCE_DIR}/cmake/Variables.cmake)

#Trouve Boost
find_package(Boost COMPONENTS serialization)

#Source & headers
file ( GLOB_RECURSE sources src/*.cpp include/*.hpp)

#### Création de l'exécutable ####
if(WINDOWS AND LINK-MAIN)
	add_executable (editeur WIN32 ${sources} )
else()
	add_executable (editeur ${sources} )
endif()

#Trouver SFML
find_package(SFML 2.0 COMPONENTS system REQUIRED)
find_package(SFML 2.0 COMPONENTS graphics REQUIRED)
find_package(SFML 2.0 COMPONENTS window REQUIRED)

#Trouver CommonsCE
find_package(CommunsCE REQUIRED)

#Trouver Biblio
find_package(Biblio REQUIRED)

#Trouver CEGUI
find_package(CEGUI REQUIRED)

#Include
include_directories(${CMAKE_SOURCE_DIR}/include ${SFML_INCLUDE_DIRS} ${COMMUNSCE_INCLUDE_DIRS}
		    ${BIBLIO_INCLUDE_DIRS} ${CEGUI_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

#Linker
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LINK_LIB ${SFML_SYSTEM_LIBRARY_DEBUG} ${SFML_WINDOW_LIBRARY_DEBUG} ${SFML_GRAPHICS_LIBRARY_DEBUG}
		  ${COMMUNSCE_LIBRARY} ${BIBLIO_LIBRARY} ${Boost_LIBRARIES})
else()
	set(LINK_LIB ${SFML_SYSTEM_LIBRARY_RELEASE} ${SFML_WINDOW_LIRARY_RELEASE} ${SFML_GRAPHICS_LIBRARY_RELEASE}
			  ${COMMUNSCE_LIBRARY} ${BIBLIO_LIBRARY} ${Boost_LIBRARIES})
endif()

if(CEGUI_DEBUG MATCHES Debug)
	set(LINK_LIB ${LINK_LIB} 
		  ${CEGUI_LIBRARY_BASE_DEBUG} ${CEGUI_LIBRARY_OPENGL_DEBUG} ${CEGUI_LIBRARY_LUA_DEBUG} ${CEGUI_LIBRARY_TOLUA_DEBUG} )
else()
	set(LINK_LIB ${LINK_LIB}
		  ${CEGUI_LIBRARY_BASE} ${CEGUI_LIBRARY_OPENGL} ${CEGUI_LIBRARY_LUA} ${CEGUI_LIBRARY_TOLUA} )
endif()

#link-main pour windows
if(WINDOWS AND LINK_SFML_MAIN)
	if(CMAKE_BUILD_TYPE MATCHES Debug)
		set(LINK_LIB ${LINK_LIB} ${SFML_MAIN_LIBRARY_DEBUG})
	else()
		set(LINK_LIB ${LINK_LIB} ${SFML_MAIN_LIBRARY_RELEASE})
	endif()
endif()

target_link_libraries(editeur ${LINK_LIB})

#Importation des datas
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
