# - Find Thor
# Find the native Thor includes and libraries
#
#  THOR_INCLUDE_DIR - where to find Thor/Config.hpp, etc.
#  THOR_LIBRARIES   - List of libraries when using libthor.
#  THOR_FOUND       - True if libthor found.

if(THOR_INCLUDE_DIR)
  # Already in cache, be silent
  set(THOR_FIND_QUIETLY TRUE)
endif(THOR_INCLUDE_DIR)

find_path(THOR_INCLUDE_DIR Thor/Config.hpp
  PATH_SUFFIXES include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw          # Fink
  /opt/local   # DarwinPorts
  /opt/csw     # Blastwave
  /opt
  ${THORDIR}
  $ENV{THORDIR})

find_library(THOR_LIBRARY_DEBUG
  thor-d
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/lib
  /usr/local
  /usr
  /sw          # Fink
  /opt/local   # DarwinPorts
  /opt/csw     # Blastwave
  /opt
  ${THORDIR}
  $ENV{THORDIR})

find_library(THOR_LIBRARY_RELEASE
  thor
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/lib
  /usr/local
  /usr
  /sw          # Fink
  /opt/local   # DarwinPorts
  /opt/csw     # Blastwave
  /opt
  ${THORDIR}
  $ENV{THORDIR})

if(THOR_LIBRARY_DEBUG OR THOR_LIBRARY_RELEASE)
  # Library found
  set(THOR_FOUND TRUE)

  # If both were found, set THOR_LIBRARY to the release version
  if(THOR_LIBRARY_DEBUG AND THOR_LIBRARY_RELEASE)
    set(THOR_LIBRARY ${THOR_LIBRARY_RELEASE})
  endif()

  if(THOR_LIBRARY_DEBUG AND NOT THOR_LIBRARY_RELEASE)
    set(THOR_LIBRARY ${THOR_LIBRARY_DEBUG})
  endif()

  if(NOT THOR_LIBRARY_DEBUG AND THOR_LIBRARY_RELEASE)
    set(THOR_LIBRARY ${THOR_LIBRARY_RELEASE})
  endif()
else()
  set(THOR_FOUND FALSE)
endif()

# Handle the QUIETLY and REQUIRED arguments and set SNDFILE_FOUND to TRUE if
# all listed variables are TRUE.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(THOR DEFAULT_MSG THOR_LIBRARY THOR_INCLUDE_DIR)

if(THOR_FOUND)
  set(THOR_LIBRARIES ${THOR_LIBRARY})
else(THOR_FOUND)
  set(THOR_LIBRARIES)
endif(THOR_FOUND)

mark_as_advanced(THOR_INCLUDE_DIR
  THOR_LIBRARY
  THOR_LIBRARY_RELEASE
  THOR_LIBRARY_DEBUG)
