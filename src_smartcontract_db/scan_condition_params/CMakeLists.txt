

set(__src
	AbstractScanConditionParameter.cpp
	ColumnIdentifierScanParam.cpp
	NumericScanParam.cpp
	StringScanParam.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_condition_params)

