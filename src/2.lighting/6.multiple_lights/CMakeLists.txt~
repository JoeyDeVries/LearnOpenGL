set( 6.multiple_lights_SOURCES
	multiple_lights.cpp )

add_executable( 6.multiple_lights ${6.multiple_lights_SOURCES} )
target_link_libraries( 6.multiple_lights ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/multiple_lights.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/multiple_lights.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lamp.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lamp.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
