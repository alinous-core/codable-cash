

set(__src
	AbstractExpressionScanColumnTarget.cpp
	BetweenScanColumnTarget.cpp
	EqualityScanColumnTarget.cpp
	ExpressionListScanColumnTarget.cpp
	FunctionCallScanColumnTarget.cpp
	IsNullScanColumnTarget.cpp
	LikeExpressionScanColumnTarget.cpp
	ParenthesisScanColumnTarget.cpp
	PlaceHolderScanColumnTarget.cpp
	RelationalExpressionScanTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_exp)

