

set(__src
	AnalyzedTypeChecker.cpp
	LeftType.cpp
	RightType.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm type_check)

