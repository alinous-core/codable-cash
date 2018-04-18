
set(__src
	funcs.cpp
)
set_parentv("${__src}" osenv osenvsrc)

set(gnodir ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/osenv/)
outgcov(report_osenv ${gnodir} "${__src}")


