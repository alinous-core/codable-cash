

set(__src
	AbstractScanConditionParameter.cpp
	BooleanScanParam.cpp
	ColumnIdentifierScanParam.cpp
	NumericScanParam.cpp
	StringScanParam.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition_params)

