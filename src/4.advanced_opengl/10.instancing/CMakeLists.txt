set( 10.instancing_SOURCES
	instancing_asteroids_instanced.cpp )

add_executable( 10.instancing ${10.instancing_SOURCES} )
target_link_libraries( 10.instancing ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/instanced_asteroids.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/instanced_asteroids.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/planet.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
