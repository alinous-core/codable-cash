

set(__src
	BetweenScanCondition.cpp
	EqualityScanCondition.cpp
	FunctionCallScanCondition.cpp
	IsNullScanCondition.cpp
	LikeScanCondition.cpp
	ParenthesisScanCondition.cpp
	RelationalScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition_exp)

