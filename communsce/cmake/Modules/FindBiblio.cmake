
# - Try to find CommunsCE
# Once done this will define
#  BIBLIO_INCLUDE_DIRS
#  BIBLIO_LIBRARY

set(BIBLIO_INCLUDE_DIRS ${BIBLIO_PATH}/include)

#Trouver lib
if(CMAKE_BUILD_TYPE MATCHES Debug)
	find_library( BIBLIO_LIBRARY
				  NAMES biblio-d
				  PATHS 
						"${BIBLIO_PATH}/lib"
						 "${BIBLIO_PATH}/lib/Debug"
						 "${BIBLIO_PATH}/lib/Release"
				)
else()
	find_library( BIBLIO_LIBRARY
				  NAMES biblio 
				  PATHS 
						  "${BIBLIO_PATH}/lib"
						  "${BIBLIO_PATH}/lib/Debug"
						  "${BIBLIO_PATH}/lib/Release"
				)
endif()


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Biblio  DEFAULT_MSG
                                  BIBLIO_LIBRARY BIBLIO_INCLUDE_DIRS)

mark_as_advanced(BIBLIO_INCLUDE_DIRS BIBLIO_LIBRARY )

