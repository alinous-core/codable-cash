

set(__src
	ParserReaderStream.cpp
	SmartContract.cpp
	SmartContractParser.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc)

