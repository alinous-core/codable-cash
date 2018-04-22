cmake_minimum_required(VERSION 2.6)


message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")


file(GLOB_RECURSE info_files *.info)

set(target_list "")

foreach(loop_var ${info_files})
	string(REGEX MATCH /test01.info mtc ${loop_var})
	string(LENGTH "${mtc}" len)
	string(REGEX MATCH /test.info mtc2 ${loop_var})
	string(LENGTH "${mtc2}" len2)
	
	if(${len} EQUAL 0 AND ${len2} EQUAL 0)
		list(APPEND target_list "${loop_var}")
	else()
		# message("#### removed ${loop_var}")
	endif()
endforeach()


list(GET target_list 0 file1)
list(GET target_list 1 file2)
list(REMOVE_AT target_list 0 1)


execute_process(
  COMMAND lcov -a ${file1} -a ${file2} -o test01.info
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  OUTPUT_QUIET
)

foreach(loop_var ${target_list})
	execute_process(
	  COMMAND cp test01.info test.info
	  COMMAND lcov -a test.info -a ${loop_var} -o test01.info
	  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	  OUTPUT_QUIET
	)
endforeach()


execute_process(
  COMMAND lcov --remove test01.info "/usr/include/*" "*/src_test/*" -o test.info
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  OUTPUT_QUIET
)


# message("############## end of CmakeReport.cmake")



