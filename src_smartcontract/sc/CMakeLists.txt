

set(__src
	AnalyzeContext.cpp
	CodeElement.cpp
	CompilationUnit.cpp
	exceptions.cpp
	SmartContract.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc)

