set( 1.depth_testing_SOURCES
	depth_testing_func.cpp )

add_executable( 1.depth_testing ${1.depth_testing_SOURCES} )
target_link_libraries( 1.depth_testing ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/depth_testing.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/depth_testing.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
