

set(__src
	CodeElement.cpp
	CompilationUnit.cpp
	CompileError.cpp
	LexError.cpp
	LexErrorHandler.cpp
	ParseErrorHandler.cpp
	ParserReaderStream.cpp
	SmartContract.cpp
	SmartContractParser.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc)

