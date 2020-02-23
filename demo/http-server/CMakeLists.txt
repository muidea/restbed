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
add_executable( httpServer ${SOURCE_DIR}/main.cpp ${SOURCE_DIR}/service/service.cpp ${SOURCE_DIR}/service/tag.cpp ${SOURCE_DIR}/service/value.cpp ${SOURCE_DIR}/service/common.cpp ${SOURCE_DIR}/service/mock.cpp )
target_link_libraries( httpServer LINK_PRIVATE ${STATIC_LIBRARY_NAME}  ${jsoncpp_LIBRARY_STATIC} ${jthread_LIBRARY_STATIC} )
