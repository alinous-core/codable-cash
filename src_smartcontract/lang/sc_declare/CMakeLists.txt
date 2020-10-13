

set(__src
	AccessControlDeclare.cpp
	ArgumentDeclare.cpp
	ArgumentsListDeclare.cpp
	ClassDeclare.cpp
	ClassDeclareBlock.cpp
	ClassExtends.cpp
	ClassImplements.cpp
	ImportDeclare.cpp
	ImportsDeclare.cpp
	ClassName.cpp
	MemberVariableDeclare.cpp
	MethodDeclare.cpp
	PackageNameDeclare.cpp
	PackageDeclare.cpp
)

handle_sub(codablecashlib "${__src}" smartcontract lang/sc_declare)

