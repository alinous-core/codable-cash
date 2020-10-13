

set(__src
	AdditiveExpressionScanColumnTarget.cpp
	MultiplicativeExpressionScanColumnTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_columns_arithmetic)

