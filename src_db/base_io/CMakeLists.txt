set(__src
	ByteBuffer.cpp
	CharBuffer.cpp
	exceptions.cpp
	File.cpp
)
set_parentv("${__src}" base_io dbiosrc)
	

set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_db/base_io)
outgcov(report_db_base_io ${gnodir} "${__src}")
