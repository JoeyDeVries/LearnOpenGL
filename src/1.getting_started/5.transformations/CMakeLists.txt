set( 5.transformations_SOURCES
	transformations.cpp )

add_executable(  5.transformations ${5.transformations_SOURCES} )
target_link_libraries(  5.transformations ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/transform.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/transform.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
