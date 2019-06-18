

set(__src
	AccessControlDeclare.cpp
	ArgumentDeclare.cpp
	ArgumentsListDeclare.cpp
	ClassDeclare.cpp
	ClassDeclareBlock.cpp
	ImportDeclare.cpp
	ImportsDeclare.cpp
	MemberVariableDeclare.cpp
	MethodDeclare.cpp
	PackageNameDeclare.cpp
	PackageDeclare.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract sc_declare)

