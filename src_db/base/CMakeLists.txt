set(__dbbasesrc
	base/SysMutex.cpp
	base/UnicodeString.cpp
)
	
set(dbbasesrc ${__dbbasesrc} PARENT_SCOPE)

set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/base/)
set(infoname testdbbase.info)
set(covdir coverage/dbbase)

set(workdir ${CMAKE_BINARY_DIR}/${covdir})


add_custom_target(report_db_base
    COMMAND mkdir -p ${covdir}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET report_db_base
    COMMAND echo "=================== GCOV crypto ===================="
	COMMAND gcov -b -l ${__dbbasesrc} -o ${gnodir}
	COMMAND lcov -c -d ${gnodir} -o ${infoname}
	#COMMAND genhtml -o output ${infoname}
	WORKING_DIRECTORY ${workdir}
)
add_dependencies(report report_db_base)
