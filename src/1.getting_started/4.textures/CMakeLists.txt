set( 4.textures_SOURCES
	textures_combined.cpp )

add_executable( 4.textures ${4.textures_SOURCES} )
target_link_libraries( 4.textures ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/texture.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/texture.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
