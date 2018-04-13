
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
target_link_libraries( ${L_PROJECT_NAME} PUBLIC ${LIB_DEPENDENCES} )
target_include_directories( ${L_PROJECT_NAME} PUBLIC ${INCLUDE_DIRS} )