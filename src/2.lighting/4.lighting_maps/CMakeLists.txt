set( 4.lighting_maps_SOURCES
	lighting_maps_specular.cpp )

add_executable( 4.lighting_maps ${4.lighting_maps_SOURCES} )
target_link_libraries( 4.lighting_maps ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lighting_maps.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lighting_maps.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lamp.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lamp.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
