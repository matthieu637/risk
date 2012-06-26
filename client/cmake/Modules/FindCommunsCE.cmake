
# - Try to find CommunsCE
# Once done this will define
#  COMMUNSCE_INCLUDE_DIRS 
#  COMMUNSCE_LIBRARY

set(COMMUNSCE_INCLUDE_DIRS ${COMMUNSCE_PATH}/include)

#Trouver lib
if(CMAKE_BUILD_TYPE MATCHES Debug)
	find_library( COMMUNSCE_LIBRARY 
				  NAMES communsCE-d 
				  PATHS 
						"${COMMUNSCE_PATH}/lib" 
						 "${COMMUNSCE_PATH}/lib/Debug" 
						 "${COMMUNSCE_PATH}/lib/Release"
				)
else()
	find_library( COMMUNSCE_LIBRARY 
				  NAMES communsCE 
				  PATHS 
						  "${COMMUNSCE_PATH}/lib" 
						  "${COMMUNSCE_PATH}/lib/Debug" 
						  "${COMMUNSCE_PATH}/lib/Release"
				)
endif()


include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(CommunsCE  DEFAULT_MSG
                                  COMMUNSCE_LIBRARY COMMUNSCE_INCLUDE_DIRS)

mark_as_advanced(COMMUNSCE_INCLUDE_DIRS COMMUNSCE_LIBRARY )

