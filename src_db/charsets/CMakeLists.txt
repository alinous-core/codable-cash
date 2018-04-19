
set(__src
	CharsetManager.cpp
	CharsetConverter.cpp
	CharsetDecoder.cpp
	CharsetEncoder.cpp
	CoderResult.cpp
	UTF8.cpp
)
set_parentv("${__src}" charsets dbcharsetssrc)

set(gnodir ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_db/charsets/)
outgcov(report_db_charsets ${gnodir} "${__src}")


