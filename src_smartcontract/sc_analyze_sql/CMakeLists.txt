

set(__src
	AnalyzedInsertColumn.cpp
	AnalyzedInsertColumnList.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract sc_analyze_sql)

