project( ZF_LOG )
cmake_minimum_required( VERSION 3.5 )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# software version
set( ${PROJECT_NAME}_VERSION_MAJOR 0 )
set( ${PROJECT_NAME}_VERSION_MINOR 1 )
set( ${PROJECT_NAME}_VERSION_PATCH 0 )

# C++11 support
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

set( ROOT_DIR       ${CMAKE_CURRENT_SOURCE_DIR} )
set( TESTS_DIR      ${ROOT_DIR}/tests )
set( THIRDPARTY_DIR ${ROOT_DIR}/thirdparty )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set( ZF_LOG_DIR ${ROOT_DIR}/ZF_LOG           CACHE PATH "ZF_LOG directory." )
set( ZF_LOG_TEST_DIR ${ROOT_DIR}/ZF_LOG_TEST CACHE PATH "ZF_LOG_TEST directory." )
set( DOC_DIR      ${ROOT_DIR}/doc            CACHE PATH "Document directory." )

# options
option( BUILD_TESTS     "Build unit tests."       OFF )
option( BUILD_EXAMPLES  "Build examples."         ON )
option( BUILD_DOCUMENT  "Build doxygen document." OFF )

message( STATUS "Options:" )
message( STATUS "BUILD_TESTS: ${BUILD_TESTS}" )
message( STATUS "BUILD_EXAMPLES: ${BUILD_EXAMPLES}" )
message( STATUS "BUILD_DOCUMENT: ${BUILD_DOCUMENT}" )

# boost?

include( cmake/zf_log.cmake )

if( BUILD_EXAMPLES )
    include( cmake/zf_log_test.cmake )
endif()

if( BUILD_DOCUMENT )
    include( cmake/doc.cmake )
endif()

if( BUILD_TESTS )
    include( cmake/tests.cmake )
endif()



