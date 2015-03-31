set( 1.model_loading_SOURCES
	model_rendered.cpp )

add_executable( 1.model_loading ${1.model_loading_SOURCES} )
target_link_libraries( 1.model_loading ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
