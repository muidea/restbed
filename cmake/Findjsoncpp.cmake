
find_library( jsoncpp_LIBRARY_STATIC libjsoncpp.a HINTS "/usr/local/lib")

find_path( jsoncpp_INCLUDE json/json.h HINTS "/usr/local/include" )

if ( jsoncpp_INCLUDE )
    set( JSONCPP_FOUND TRUE )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DJSONCPP_STANDALONE=YES" )

    message( STATUS "Found JSONCPP include at: ${jsoncpp_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate JSONCPP dependency." )
endif ( )
