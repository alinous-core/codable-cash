
set(src
	testmain.cpp
)

set(testsrc
	test_arraylist.cpp
	test_character.cpp
	test_exceptions.cpp
	test_hashmap.cpp
	test_integer.cpp
	test_misc.cpp
	test_stack_release.cpp
	test_thread.cpp
	test_unicode_string.cpp
)

foreach(loop_var IN LISTS testsrc)
	list(APPEND __testsrc db_base/${loop_var})
endforeach()
set(db_base_test_src ${__testsrc} PARENT_SCOPE)


add_executable(db_base_test ${src} ${testsrc})
target_link_libraries(db_base_test codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

#add_test(testdbbase db_base_test -v)


set(target_name report_test_db_base)
set(gnodir ${CMAKE_BINARY_DIR}/src_test/CMakeFiles/testall.dir/db_base/)

set(infoname ${target_name}.info)
set(covdir coverage/${target_name})
set(workdir ${CMAKE_BINARY_DIR}/${covdir})


add_custom_target(${target_name}
    COMMAND mkdir -p ${covdir}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET ${target_name}
    COMMAND echo "=================== GCOV ${target_name} ===================="
	COMMAND lcov -c -d ${gnodir} -o ${infoname}
	WORKING_DIRECTORY ${workdir}
)
add_dependencies(lcov ${target_name})



