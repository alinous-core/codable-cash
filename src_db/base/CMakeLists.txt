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


outgcov(report_db_base ${CMAKE_BINARY_DIR}/CMakeFiles/testall.dir/src_db/base/ "${__src}")
