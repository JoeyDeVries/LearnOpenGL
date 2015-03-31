set( 8.advanced_glsl_SOURCES
	advanced_glsl_uniform_buffer_objects.cpp )

add_executable( 8.advanced_glsl ${8.advanced_glsl_SOURCES} )
target_link_libraries(  8.advanced_glsl ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/blue.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/green.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/red.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/yellow.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/uniform_buffers.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
