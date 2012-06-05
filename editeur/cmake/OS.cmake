
# Détection de l'OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(WINDOWS 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX 1)
else()
    message(WARNING "Unsupported operating system")
    return()
endif()
