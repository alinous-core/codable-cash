

set(__src
	AbstractTypeCheckTarget.cpp
	AnalyzedTypeChecker.cpp
	LeftType.cpp
	RightType.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm type_check)

