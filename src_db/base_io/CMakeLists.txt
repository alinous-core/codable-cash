set(__src
	ByteBuffer.cpp
	CharBuffer.cpp
	exceptions.cpp
	File.cpp
)
set_parentv("${__src}" base_io dbiosrc)
	

set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/base_io/)
outgcov(report_db_base_io ${gnodir} "${__src}")
