#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_PATH
# GLEW_LIBRARY
#
IF (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
	${CMAKE_SOURCE_DIR}/includes
	$ENV{PROGRAMFILES}/GLEW/include
	${GLEW_ROOT_DIR}/include
	DOC "The directory where GL/glew.h resides")
	IF (NV_SYSTEM_PROCESSOR STREQUAL "AMD64")
		FIND_LIBRARY( GLEW_LIBRARY
			NAMES glew64 glew64s
			PATHS
			$ENV{PROGRAMFILES}/GLEW/lib
			${PROJECT_SOURCE_DIR}/src/nvgl/glew/bin
			${PROJECT_SOURCE_DIR}/src/nvgl/glew/lib
			DOC "The GLEW library (64-bit)"
		)
	ELSE(NV_SYSTEM_PROCESSOR STREQUAL "AMD64")
		FIND_LIBRARY( GLEW_LIBRARY
			NAMES glew GLEW glew32 glew32s
			PATHS
			${CMAKE_SOURCE_DIR}/lib
			$ENV{PROGRAMFILES}/GLEW/lib
			${PROJECT_SOURCE_DIR}/src/nvgl/glew/bin
			${PROJECT_SOURCE_DIR}/src/nvgl/glew/lib
			DOC "The GLEW library"
		)
	ENDIF(NV_SYSTEM_PROCESSOR STREQUAL "AMD64")
ELSE (WIN32)
	FIND_PATH( GLEW_INCLUDE_PATH GL/glew.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		${GLEW_ROOT_DIR}/include
		DOC "The directory where GL/glew.h resides")
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES GLEW glew
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLEW_ROOT_DIR}/lib
		DOC "The GLEW library")
ENDIF (WIN32)
SET(GLEW_FOUND "NO")
IF (GLEW_INCLUDE_PATH AND GLEW_LIBRARY)
	SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
	SET(GLEW_FOUND "YES")
ENDIF (GLEW_INCLUDE_PATH AND GLEW_LIBRARY)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_LIBRARY GLEW_INCLUDE_PATH)
