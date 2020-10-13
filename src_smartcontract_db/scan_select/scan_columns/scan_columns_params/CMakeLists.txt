

set(__src
	AbstractColumnParam.cpp
	BooleanLiteralColumnParam.cpp
	NumberLiteralColumnParam.cpp
	StringLiteralColumnParam.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_db scan_select/scan_columns/scan_columns_params)

