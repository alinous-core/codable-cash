
set(__src
	funcs.cpp
)
set_parentv("${__src}" osenv osenvsrc)

set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_db/osenv/)
outgcov(report_osenv ${gnodir} "${__src}")


