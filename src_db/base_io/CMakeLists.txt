set(__src
	ByteBuffer.cpp
	CharBuffer.cpp
	exceptions.cpp
	File.cpp
)

foreach(loop_var IN LISTS __src)
	list(APPEND __parentsrc base_io/${loop_var})
endforeach()
set(dbiosrc ${__parentsrc} PARENT_SCOPE)
	

set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/base_io/)
outgcov(report_db_base_io ${gnodir} "${__src}")
