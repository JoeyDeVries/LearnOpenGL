# - Try to find FreeType2
# Once done, this will define
#
# FreeType2_FOUND - system has FreeType2
# FreeType2_INCLUDE_DIR - the FreeType2 include directories
# FreeType2_LIBRARIES - link these to use FreeType2
FIND_PATH( FREETYPE2_INCLUDE_DIR freetype2/ft2build.h
	/usr/include
	/usr/local/include
	/opt/local/include
    /usr/local/opt/freetype/include
	${CMAKE_SOURCE_DIR}/includes
)
FIND_LIBRARY( FREETYPE2_LIBRARY freetype
	/usr/lib64
	/usr/lib
	/usr/local/lib
	/opt/local/lib
    /usr/local/opt/freetype/lib
	${CMAKE_SOURCE_DIR}/lib
)
IF(FREETYPE2_INCLUDE_DIR AND FREETYPE2_LIBRARY)
	SET( FREETYPE2_FOUND TRUE )
	SET( FREETYPE2_LIBRARIES ${FREETYPE2_LIBRARY} )
ENDIF(FREETYPE2_INCLUDE_DIR AND FREETYPE2_LIBRARY)
IF(FREETYPE2_FOUND)
	IF(NOT FREETYPE2_FIND_QUIETLY)
	MESSAGE(STATUS "Found FREETYPE2: ${FREETYPE2_LIBRARY}")
	ENDIF(NOT FREETYPE2_FIND_QUIETLY)
ELSE(FREETYPE2_FOUND)
	IF(FREETYPE2_FIND_REQUIRED)
	MESSAGE(FATAL_ERROR "Could not find libfreetype")
	ENDIF(FREETYPE2_FIND_REQUIRED)
ENDIF(FREETYPE2_FOUND)
