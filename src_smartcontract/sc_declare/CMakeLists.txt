

set(__src
	ClassDeclare.cpp
	ClassDeclareBlock.cpp
	MemberVariableDeclare.cpp
	MethodDeclare.cpp
	PackageDeclare.cpp
	TypeDeclare.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_declare)

