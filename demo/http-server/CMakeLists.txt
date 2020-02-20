project( "integration test suite" )

cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCATCH_CONFIG_MAIN" )

include_directories( SYSTEM ${catch_INCLUDE} )

#
# Build
#
add_executable( httpServer ${SOURCE_DIR}/main.cpp )
target_link_libraries( httpServer ${STATIC_LIBRARY_NAME} )
