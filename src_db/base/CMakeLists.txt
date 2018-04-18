set(__src
	Character.cpp
	Exception.cpp
	exceptions.cpp
	Integer.cpp
	RawBitSet.cpp
	SysMutex.cpp
	UnicodeString.cpp
)

foreach(loop_var IN LISTS __src)
	list(APPEND __parentsrc base/${loop_var})
endforeach()
set(dbbasesrc ${__parentsrc} PARENT_SCOPE)


outgcov(report_db_base ${CMAKE_BINARY_DIR}/src_db/CMakeFiles/alinousdb.dir/base/ "${__src}")
