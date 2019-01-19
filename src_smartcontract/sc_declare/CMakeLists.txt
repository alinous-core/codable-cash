

set(__src
	ArgumentDeclare.cpp
	ClassDeclare.cpp
	ClassDeclareBlock.cpp
	ITypeDeclare.cpp
	MemberVariableDeclare.cpp
	MethodDeclare.cpp
	PackageNameDeclare.cpp
	PackageDeclare.cpp
	TypeDeclare.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_declare)

