
set( L_PROJECT_NAME zf_log )
set( U_PROJECT_NAME ZF_LOG )

# verify existence
if( NOT IS_DIRECTORY ${${U_PROJECT_NAME}_DIR} )
    message( FATAL_ERROR "Can't load ${${U_PROJECT_NAME}_DIR}, directory doesn't exists. ${${U_PROJECT_NAME}_DIR}" )
    return()
else()
    set( PROJECT_DIR ${${U_PROJECT_NAME}_DIR} )
endif()

# grab the sources
file( GLOB SOURCES ${PROJECT_DIR}/src/*.cpp ${PROJECT_DIR}/include/*.hpp ${PROJECT_DIR}/include/*.h )

# create target
add_library( ${L_PROJECT_NAME} STATIC ${SOURCES} )


set( 
    INCLUDE_DIRS
    ${PROJECT_DIR}/include
)
# add target include

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.67.0 COMPONENTS date_time filesystem system)

target_link_libraries( ${L_PROJECT_NAME} PUBLIC ${LIB_DEPENDENCES} ${Boost_LIBRARIES} )
target_include_directories( ${L_PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} )