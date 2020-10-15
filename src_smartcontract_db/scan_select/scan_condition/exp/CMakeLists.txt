

set(__src
	BetweenScanCondition.cpp
	EqualityScanCondition.cpp
	ExpressionListScanCondition.cpp
	FunctionCallScanCondition.cpp
	InExpressionScanCondition
	IsNullScanCondition.cpp
	LikeScanCondition.cpp
	ParenthesisScanCondition.cpp
	RelationalScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_condition/exp)

