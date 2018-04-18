set(__src
	Character.cpp
	Exception.cpp
	exceptions.cpp
	Integer.cpp
	RawBitSet.cpp
	SysMutex.cpp
	UnicodeString.cpp
)
set_parentv("${__src}" base dbbasesrc)


outgcov(report_db_base ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/base/ "${__src}")
