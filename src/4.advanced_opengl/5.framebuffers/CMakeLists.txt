set( 5.framebuffers_SOURCES
	framebuffers_screen_texture.cpp )

add_executable( 5.framebuffers ${5.framebuffers_SOURCES} )
target_link_libraries(  5.framebuffers ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/framebuffers.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/framebuffers.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/framebuffers_screen.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/framebuffers_screen.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
