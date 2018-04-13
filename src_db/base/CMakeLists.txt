set(__dbbasesrc
	base/SysMutex.cpp
)
	
set(dbbasesrc ${__dbbasesrc} PARENT_SCOPE)

set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/base/)
set(infoname testdbbase.info)
set(workdir ${CMAKE_BINARY_DIR}/coverage/crypto)

add_custom_target(report_db_base
    COMMAND mkdir -p coverage/crypto
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET report_db_base
    COMMAND echo "=================== GCOV crypto ===================="
	COMMAND gcov -b  ${__cryptosrc} -o ${gnodir}
	COMMAND lcov -c -d ${gnodir} -o ${infoname}
	COMMAND genhtml -o output ${infoname}
	WORKING_DIRECTORY ${workdir}
)
add_dependencies(report report_db_base)
