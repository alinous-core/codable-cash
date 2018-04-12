cmake_minimum_required(VERSION 2.6)
project(codablecash)


add_subdirectory(src_ext)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Debug Build")
		
	set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -fmessage-length=0 -g -coverage -fprofile-arcs -ftest-coverage")
	set(CMAKE_C_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
	
	set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
	set(CMAKE_C_OUTPUT_EXTENSION_REPLACE ON)
	
	message(STATUS "Debug Build" ${CMAKE_CXX_FLAGS})
elseif(CMAKE_BUILD_TYPE STREQUAL "ReleaseTest")
	set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -fmessage-length=0 -g3 -march=native -MMD -MP -MF")
else()
	set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -Wall -fmessage-length=0 -O3 -march=native -MMD -MP -MF")
endif()


if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "ReleaseTest")
	if(DEFINED ENV{CPPUTEST_HOME})
	    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
	    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
	    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
	    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
	else()
	    find_package(PkgConfig REQUIRED)
	    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
	    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
	endif()
	
	enable_testing()
	
	add_custom_target(report)
endif()


set(src
	"AlinousStore.cpp"
)

#message("INCLUDE : ${PROJECT_SOURCE_DIR}/src/")
include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/src_ext/)

add_subdirectory(src)

add_executable(codablecash ${src})
target_link_libraries(codablecash codablelib extlib gmp)

#
# Test Codes
#
add_subdirectory(src_test)

