set( 1.hello_window_SOURCES
	hellowindow2.cpp )

add_executable( 1.hello_window ${1.hello_window_SOURCES} )
target_link_libraries( 1.hello_window ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
