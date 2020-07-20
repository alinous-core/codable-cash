

set(__src
	AbstractScanCondition.cpp
	EqualityScanCondition.cpp
	RootScanCondition.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition)

