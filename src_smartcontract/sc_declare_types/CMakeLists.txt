

set(__src
	AbstractPrimitiveType.cpp
	CharType.cpp
	IntType.cpp
	LongType.cpp
	ShortType.cpp
	StringType.cpp
	VoidType.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_declare_types)

