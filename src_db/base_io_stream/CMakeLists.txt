set(__src
	InputStream.cpp
)
set_parentv("${__src}" base_io_stream dbiostreamsrc)
	

set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_db/base_io_stream)
outgcov(report_db_base_io_stream ${gnodir} "${__src}")
