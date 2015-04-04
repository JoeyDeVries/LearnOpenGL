# - Locate SOIL library
# This module defines
# SOIL_LIBRARY, the name of the library to link against
# SOIL_FOUND
# SOIL_INCLUDE_DIR, where to find SOIL.h
# To Adding search path, set SOIL_ROOT_DIR as follows
# set(SOIL_ROOT_DIR "path/to/soil")
# or launch cmake with -DSOIL_ROOT_DIR="/path/to/SOIL_ROOT_DIR".
#
# author: Kazunori Kimura
# email : kazunori.abu@gmail.com
#
# revisions: github.com/zwookie

find_path(SOIL_INCLUDE_DIR SOIL.h
	/usr/include
	/usr/local/include
	/opt/local/include
	${CMAKE_SOURCE_DIR}/includes
)

find_library(SOIL_LIBRARY SOIL
	/usr/lib64
	/usr/lib
	/usr/local/lib
	/opt/local/lib
	${CMAKE_SOURCE_DIR}/lib
)

IF(SOIL_INCLUDE_DIR AND SOIL_LIBRARY)
	SET( SOIL_FOUND TRUE )
	SET( SOIL_LIBRARIES ${SOIL_LIBRARY} )
ENDIF(SOIL_INCLUDE_DIR AND SOIL_LIBRARY)
IF(SOIL_FOUND)
	IF(NOT SOIL_FIND_QUIETLY)
	MESSAGE(STATUS "Found SOIL: ${SOIL_LIBRARY}")
	ENDIF(NOT SOIL_FIND_QUIETLY)
ELSE(SOIL_FOUND)
	IF(SOIL_FIND_REQUIRED)
	MESSAGE(FATAL_ERROR "Could not find libSOIL")
	ENDIF(SOIL_FIND_REQUIRED)
ENDIF(SOIL_FOUND)
