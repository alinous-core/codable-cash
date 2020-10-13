

set(__src
	CodeElement.cpp
	CompilationUnit.cpp
	exceptions.cpp
	SmartContract.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract engine/sc)

