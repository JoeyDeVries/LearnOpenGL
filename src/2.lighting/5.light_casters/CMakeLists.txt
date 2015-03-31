set( 5.light_casters_SOURCES
	light_casters_spotlight_soft.cpp )

add_executable( 5.light_casters ${5.light_casters_SOURCES} )
target_link_libraries( 5.light_casters ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/light_casters.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/light_casters.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lamp.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lamp.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
