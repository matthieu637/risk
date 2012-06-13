# - Try to find CEGUI
# Once done this will define
#  CEGUI_INCLUDE_DIRS
#  CEGUI_LIBRARY_BASE
#  CEGUI_LIBRARY_BASE_DEBUG
#  CEGUI_LIBRARY_OPENGL
#  CEGUI_LIBRARY_OPENGL_DEBUG


#Trouver include
FIND_PATH(CEGUI_INCLUDE_DIR CEGUI/CEGUI.h
    PATHS
    $ENV{CEGUI_DIR}/include
    $ENV{CEGUIDIR}/include
    $ENV{CEGUI_ROOT}/include
    ${DELTA3D_EXT_DIR}/inc
    ${DELTA3D_EXT_DIR}/Frameworks
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    /usr/freeware/include
)

include(FindPackageHandleStandardArgs)

#Trouver lib
if(CEGUI_DEBUG MATCHES Debug)
	find_library( CEGUI_LIBRARY_BASE_DEBUG
				  NAMES CEGUIBase-d
				  PATHS
				  /usr/local/lib
				  /usr/lib
				  /sw/lib
				  /opt/local/lib
				  /opt/csw/lib
				  /opt/lib
				)
				
	find_library( CEGUI_LIBRARY_OPENGL_DEBUG
				  NAMES CEGUIOpenGLRenderer-d
				  PATHS
				  /usr/local/lib
				  /usr/lib
				  /sw/lib
				  /opt/local/lib
				  /opt/csw/lib
				  /opt/lib
				)

	find_package_handle_standard_args(CEGUI  DEFAULT_MSG
		CEGUI_LIBRARY_BASE_DEBUG 
		CEGUI_LIBRARY_OPENGL_DEBUG
		CEGUI_INCLUDE_DIR
		)

	mark_as_advanced(CEGUI_INCLUDE_DIR 
		CEGUI_LIBRARY_BASE_DEBUG
		CEGUI_LIBRARY_OPENGL_DEBUG 
		CEGUI_LIBRARY_LUA_DEBUG
		CEGUI_LIBRARY_TOLUA_DEBUG )
					
else()
	find_library( CEGUI_LIBRARY_BASE
				  NAMES CEGUIBase
				  PATHS
				  /usr/local/lib
				  /usr/lib
				  /sw/lib
				  /opt/local/lib
				  /opt/csw/lib
				  /opt/lib
				)

	find_library( CEGUI_LIBRARY_OPENGL
				  NAMES CEGUIOpenGLRenderer
				  PATHS
				  /usr/local/lib
				  /usr/lib
				  /sw/lib
				  /opt/local/lib
				  /opt/csw/lib
				  /opt/lib
				)

	

	find_package_handle_standard_args(CEGUI  DEFAULT_MSG
				      CEGUI_LIBRARY_BASE CEGUI_LIBRARY_OPENGL CEGUI_INCLUDE_DIR)

	mark_as_advanced(CEGUI_INCLUDE_DIR CEGUI_LIBRARY_BASE CEGUI_LIBRARY_OPENGL)
endif()
