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
find_path(SOIL_INCLUDE_DIR_TMP SOIL.h
	HINTS ${SOIL_ROOT_DIR}
	PATH_SUFFIXES include/SOIL SOIL include
)
if(${SOIL_INCLUDE_DIR_TMP} STREQUAL "SOIL_INCLUDE_DIR_TMP-NOTFOUND")
	set(SOIL_INCLUDE_DIR ${SOIL_INCLUDE_DIR_TMP})
else()
	string(REGEX REPLACE "(.*)/SOIL" "\\1" SOIL_INCLUDE_DIR ${SOIL_INCLUDE_DIR_TMP})
endif()

find_library(SOIL_LIBRARY
	NAMES SOIL
	HINTS ${SOIL_ROOT_DIR}
	PATH_SUFFIXES lib
)

unset(INCLUDE_SEARCH_PATH)
unset(LIB_SEARCH_PATH)
unset(SOIL_INCLUDE_DIR_TMP)
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SOIL
REQUIRED_VARS SOIL_LIBRARY SOIL_INCLUDE_DIR)
