set( 7.camera_SOURCES
	camera_with_class.cpp )

add_executable(  7.camera ${7.camera_SOURCES} )
target_link_libraries(  7.camera ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/coordinate_systems.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/coordinate_systems.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
