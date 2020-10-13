

set(__src
	AbstractTypeCheckTarget.cpp
	AnalyzedTypeChecker.cpp
	InternalTypeChecker.cpp
	LeftType.cpp
	RightType.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm/type_check)

