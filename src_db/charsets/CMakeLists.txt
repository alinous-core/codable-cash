
set(__src
	CharsetManager.cpp
	CharsetConverter.cpp
	CharsetDecoder.cpp
	CharsetEncoder.cpp
	CoderResult.cpp
	UTF8.cpp
)

foreach(loop_var IN LISTS __src)
	list(APPEND __parentsrc charsets/${loop_var})
endforeach()
set(dbcharsetssrc ${__parentsrc} PARENT_SCOPE)


set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/charsets/)
outgcov(report_db_charsets ${gnodir} "${__src}")


