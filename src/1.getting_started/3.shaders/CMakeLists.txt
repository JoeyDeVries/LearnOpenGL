set( 3.shaders_SOURCES
	shaders-using-object.cpp )

add_executable( 3.shaders ${3.shaders_SOURCES} )
target_link_libraries( 3.shaders ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/basic.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/basic.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
