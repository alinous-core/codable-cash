

set(__src
	CodeElement.cpp
	CompilationUnit.cpp
	ParserReaderStream.cpp
	SmartContract.cpp
	SmartContractParser.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc)

