
find_library( jthread_LIBRARY_STATIC libjthread.a HINTS "/usr/local/lib")

find_path( jthread_INCLUDE jthread/jthread.h HINTS "/usr/local/include" )

if ( jthread_INCLUDE )
    set( JTHREAD_FOUND TRUE )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DJTHREAD_STANDALONE=YES" )

    message( STATUS "Found JTHREAD include at: ${jthread_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate JTHREAD dependency." )
endif ( )
