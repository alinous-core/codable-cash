

set(__src
	AbstractExpressionScanColumnTarget.cpp
	FunctionCallScanColumnTarget.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_columns_exp)

