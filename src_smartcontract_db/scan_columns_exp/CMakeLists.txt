

set(__src
	AbstractExpressionScanColumnTarget.cpp
	BetweenScanColumnTarget.cpp
	EqualityScanColumnTarget.cpp
	FunctionCallScanColumnTarget.cpp
	IsNullScanColumnTarget.cpp
	ParenthesisScanColumnTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_exp)

