
set(src
	testmain.cpp
)

set(testsrc
	test_charsets.cpp
)

foreach(loop_var IN LISTS testsrc)
	list(APPEND __testsrc db_charsets/${loop_var})
endforeach()
set(db_charset_test_src ${__testsrc} PARENT_SCOPE)


set(testtarget db_charset_test)

add_executable(${testtarget} ${src} ${testsrc})
target_link_libraries(${testtarget} codablelib extlib alinousdb pthread gmp ${CPPUTEST_LDFLAGS})

#add_test(${testtarget} ${testtarget} -v)


set(target_name report_test_db_charsets)
set(gnodir ${CMAKE_BINARY_DIR}/src_test/CMakeFiles/testall.dir/db_charsets)

set(infoname ${target_name}.info)
set(covdir coverage/${target_name})
set(workdir ${CMAKE_BINARY_DIR}/${covdir})


add_custom_target(${target_name}
    COMMAND mkdir -p ${covdir}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET ${target_name}
    COMMAND echo "=================== GCOV ${target_name} ===================="
    COMMAND gcov -b -l ${testsrc} -o ${gnodir}
	COMMAND lcov -c -d ${gnodir} -o ${infoname}
	WORKING_DIRECTORY ${workdir}
)
add_dependencies(lcov ${target_name})
