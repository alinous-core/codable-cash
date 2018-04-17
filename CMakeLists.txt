cmake_minimum_required(VERSION 2.6)
project(codablecash)


add_subdirectory(src_ext)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Debug Build")
		
	set(CMAKE_CXX_FLAGS "-std=c++0x -D__cplusplus=201103L -fmessage-length=0 -g -O0 -coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
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
	set(infofiles
		#coverage/report_crypto/report_crypto.info
		#coverage/report_db_base/report_db_base.info
		#coverage/report_db_base_io/report_db_base_io.info
		#coverage/report_db_charsets/report_db_charsets.info
		#coverage/report_test_db_base/report_test_db_base.info
		#coverage/report_test_db_base_io/report_test_db_base_io.info
		coverage/test.info
	)
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
		COMMAND lcov -a test01.info -a report_db_base_io/report_db_base_io.info -o test02.info
		COMMAND lcov -a test02.info -a report_db_charsets/report_db_charsets.info -o test03.info
		COMMAND lcov -a test03.info -a report_test_db_base/report_test_db_base.info -o test04.info
		COMMAND lcov -a test04.info -a report_test_db_base_io/report_test_db_base_io.info -o test05.info
		COMMAND lcov -a test05.info -a report_test_db_charsets/report_test_db_charsets.info -o test.info
				
		COMMAND lcov --remove test05.info '/usr/include/*' '*/src_test/*' -o test.info
		
		WORKING_DIRECTORY ${workdir}
)
	add_dependencies(report lcov)
	
endif()

#[[ =========================================================================================== ]]#

function(outgcov target_name gnodir)
	set(infoname ${target_name}.info)
	set(covdir coverage/${target_name})
	set(workdir ${CMAKE_BINARY_DIR}/${covdir})
	
	
	add_custom_target(${target_name}
	    COMMAND mkdir -p ${covdir}
	    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	    )
	
	add_custom_command(TARGET ${target_name}
	    COMMAND echo "=================== GCOV ${target_name} ===================="
	    COMMAND gcov -b ${testsrc} -o ${gnodir}
		COMMAND lcov -c -d ${gnodir} -o ${infoname}
		WORKING_DIRECTORY ${workdir}
	)
	add_dependencies(lcov ${target_name})
endfunction(outgcov)

#[[ =========================================================================================== ]]#

set(src
	"AlinousStore.cpp"
)

include_directories(${PROJECT_SOURCE_DIR}/src_ext/)
include_directories(${PROJECT_SOURCE_DIR}/src_db/)
include_directories(${PROJECT_SOURCE_DIR}/src/)

add_subdirectory(src_db)
add_subdirectory(src)

add_executable(codablecash ${src})
target_link_libraries(codablecash codablelib extlib alinousdb gmp)

#
# Test Codes
#
add_subdirectory(src_test)

