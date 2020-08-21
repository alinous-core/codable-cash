

set(__src
	AbstractExpressionScanColumnTarget.cpp
	BetweenScanColumnTarget.cpp
	EqualityScanColumnTarget.cpp
	FunctionCallScanColumnTarget.cpp
	IsNullScanColumnTarget.cpp
	ParenthesisScanColumnTarget.cpp
	PlaceHolderScanColumnTarget.cpp
	RelationalExpressionScanTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_exp)

