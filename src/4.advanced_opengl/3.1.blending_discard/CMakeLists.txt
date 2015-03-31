set( 3.1.blending_discard_SOURCES
	blending_discard.cpp )

add_executable(  3.1.blending_discard ${3.1.blending_discard_SOURCES} )
target_link_libraries(  3.1.blending_discard ${LEARNOPENGL_LIBS} )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/blending_discard.vs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/blending_discard.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
