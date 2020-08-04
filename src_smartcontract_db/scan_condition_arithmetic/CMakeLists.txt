

set(__src
	AdditiveScanCondition.cpp
	MultiplicativeScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition_arithmetic)

