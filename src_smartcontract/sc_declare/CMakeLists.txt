

set(__src
	ArgumentDeclare.cpp
	ClassDeclare.cpp
	ClassDeclareBlock.cpp
	MemberVariableDeclare.cpp
	MethodDeclare.cpp
	PackageDeclare.cpp
	TypeDeclare.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_declare)

