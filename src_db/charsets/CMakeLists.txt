set(__src
	charsets/CharsetManager.cpp
	charsets/CharsetConverter.cpp
	charsets/CharsetDecoder.cpp
	charsets/CharsetEncoder.cpp
	charsets/CoderResult.cpp
	charsets/UTF8.cpp
)
	
set(dbcharsetssrc ${__src} PARENT_SCOPE)

set(target_name report_db_charsets)
set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/charsets/)

set(infoname ${target_name}.info)
set(covdir coverage/${target_name})
set(workdir ${CMAKE_BINARY_DIR}/${covdir})

add_custom_target(${target_name}
    COMMAND mkdir -p ${covdir}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET ${target_name}
    COMMAND echo "=================== GCOV ${target_name} ===================="
	COMMAND gcov -b -l ${__src} -o ${gnodir}
	COMMAND lcov -c -d ${gnodir} -o ${infoname}
	WORKING_DIRECTORY ${workdir}
)
add_dependencies(lcov ${target_name})


