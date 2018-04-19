cmake_minimum_required(VERSION 2.6)
project(codablecash)


add_subdirectory(src_ext)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Debug Build")
		
	set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -fmessage-length=0 -g -O0 -coverage")
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
	    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.4)
	    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
	endif()
	
	enable_testing()
	
	# Report
	set(infofiles coverage/test.info)
	add_custom_target(report)
	add_custom_command(TARGET report
		COMMAND genhtml --no-function-coverage --title "CodableCash Test Report" -s -p ${PROJECT_SOURCE_DIR} -o html_report ${infofiles}
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		)
		
	set(covdir coverage/)
	set(workdir ${CMAKE_BINARY_DIR}/${covdir})
		
	add_custom_target(lcov
	    COMMAND mkdir -p ${covdir}
	    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	    )
	
	add_custom_command(TARGET lcov
	    COMMAND echo "=================== LCOV ===================="
		
		COMMAND lcov -a report_crypto/report_crypto.info -a report_db_base/report_db_base.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_db_base_io/report_db_base_io.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_db_base_io_stream/report_db_base_io_stream.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_db_charsets/report_db_charsets.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_osenv/report_osenv.info -o test01.info
		COMMAND cp test01.info test.info
		
		COMMAND lcov -a test.info -a report_test_crypto/report_test_crypto.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_test_db_base/report_test_db_base.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_test_db_base_io/report_test_db_base_io.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_db_base_io_stream/report_db_base_io_stream.info -o test01.info
		COMMAND cp test01.info test.info		
		COMMAND lcov -a test.info -a report_test_db_charsets/report_test_db_charsets.info -o test01.info
		COMMAND cp test01.info test.info
		COMMAND lcov -a test.info -a report_test_utils/report_test_utils.info -o test01.info
		
		
		COMMAND rm test.info
				
		COMMAND lcov --remove test01.info '/usr/include/*' '*/src_test/*' -o test.info
		
		WORKING_DIRECTORY ${workdir}
)
	add_dependencies(report lcov)
	
endif()

#[[ =========================================================================================== ]]#

macro(outgcov target_name gnodir srclist)
	set(infoname ${target_name}.info)
	set(covdir coverage/${target_name})
	set(workdir ${CMAKE_BINARY_DIR}/${covdir})
	
	add_custom_target(${target_name}
	    COMMAND mkdir -p ${covdir}
	    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	    )
	
	add_custom_command(TARGET ${target_name}
	    COMMAND echo "=================== LCOV ${target_name} ===================="
	    COMMAND gcov -b ${srclist} -o ${gnodir}
		COMMAND lcov -c -d ${gnodir} -o ${infoname}
		WORKING_DIRECTORY ${workdir}
	)
	add_dependencies(lcov ${target_name})
endmacro(outgcov)

macro(set_parentv srclist prefix var_name)
	set(__tmptestsrc "")
	foreach(loop_var ${srclist})
		list(APPEND __tmptestsrc ${prefix}/${loop_var})
	endforeach()
	set(${var_name} ${__tmptestsrc} PARENT_SCOPE)
endmacro(set_parentv)

#[[ =========================================================================================== ]]#

set(src
	"AlinousStore.cpp"
)

include_directories(${PROJECT_SOURCE_DIR}/src_ext/)
include_directories(${PROJECT_SOURCE_DIR}/src_db/)
include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/src_test/)

add_subdirectory(src_db)
add_subdirectory(src)

add_executable(codablecash ${src} ${top_src} ${top_src_db})
target_link_libraries(codablecash extlib gmp)


if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "ReleaseTest")
	#
	# Test Codes
	#
	add_subdirectory(src_test)
	
	set(testtarget testall)
	add_executable(${testtarget} src_test/testallmain.cpp ${top_src} ${top_src_db} ${top_testsrc})
	target_link_libraries(${testtarget} extlib pthread gmp ${CPPUTEST_LDFLAGS})
	
	add_test(${testtarget} ${testtarget} -v)
endif()
