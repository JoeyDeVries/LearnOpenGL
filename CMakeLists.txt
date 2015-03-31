cmake_minimum_required (VERSION 2.8)
cmake_policy(VERSION 2.8)
 # cmake_policy(SET CMP0037 OLD)

project (LEARNOPENGL)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
link_directories(${CMAKE_SOURCE_DIR}/lib )
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

find_package(GLM_REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIRS}")
find_package(GLFW3_REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP_REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")	
find_package(SOIL_REQUIRED)
message(STATUS "Found SOIL in ${SOIL_INCLUDE_DIR}")
find_package(GLEW_REQUIRED)	
message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")

set(LEARNOPENGL_LIBS lib)
set(LEARNOPENGL_INCLUDE ${LEARNOPENGL_SOURCE_DIR}/includes)

list( APPEND LEARNOPENGL_INCLUDE ${GLM_INCLUDE_DIRS} )
list( APPEND LEARNOPENGL_INCLUDE ${GLFW3_INCLUDE_DIRS} )
list( APPEND LEARNOPENGL_LIBS ${GLFW3_LIBRARY} )
list( APPEND LEARNOPENGL_INCLUDE ${GLEW_INCLUDE_DIRS} )
list( APPEND LEARNOPENGL_LIBS ${GLEW_LIBRARY} )
list( APPEND LEARNOPENGL_INCLUDE ${SOIL_INCLUDE_DIRS} )
list( APPEND LEARNOPENGL_LIBS ${SOIL_LIBRARY} )
list( APPEND LEARNOPENGL_INCLUDE ${ASSIMP_INCLUDE_DIRS} )
list( APPEND LEARNOPENGL_LIBS ${ASSIMP_LIBRARY} )

if(WIN32)
	find_package( OpenGL REQUIRED )
	list( APPEND LEARNOPENGL_LIBS ${OPENGL_gl_LIBRARY} )
endif(WIN32)

if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
	
	find_package( OpenGL REQUIRED )
	list( APPEND LEARNOPENGL_LIBS ${OPENGL_gl_LIBRARY} )
	
	find_package( Threads REQUIRED )
	list( APPEND LEARNOPENGL_LIBS ${CMAKE_THREAD_LIBS_INIT} )
	
	find_package( X11 REQUIRED )
	list( APPEND LEARNOPENGL_LIBS ${X11_Xrandr_LIB} ${X11_Xxf86vm_LIB} ${X11_Xi_LIB} )
	
	find_library( RT_LIB rt )
	list( APPEND LEARNOPENGL_LIBS ${RT_LIB} )
endif(UNIX)

IF(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} /usr/local/lib/libglfw.a)
ENDIF(APPLE)

set(LEARNOPENGL_LIBS ${LIBS} ${APPLE_LIBS})

include_directories( ${LEARNOPENGL_INCLUDE} )

add_subdirectory( 1.getting_started/1.hello_window )
add_subdirectory( 1.getting_started/2.hello_triangle )
add_subdirectory( 1.getting_started/3.shaders )
add_subdirectory( 1.getting_started/4.textures )
add_subdirectory( 1.getting_started/5.transformations )
add_subdirectory( 1.getting_started/6.coordinate_systems )
add_subdirectory( 1.getting_started/7.camera )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dlls DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
