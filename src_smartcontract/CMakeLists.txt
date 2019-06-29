
set(__dirsrc "")

# import source codes
add_subdirectory(compiler)
add_subdirectory(sc)
add_subdirectory(sc_analyze)
add_subdirectory(sc_analyze_stack)
add_subdirectory(sc_declare)
add_subdirectory(sc_declare_types)
add_subdirectory(sc_expression)
add_subdirectory(sc_expression_arithmetic)
add_subdirectory(sc_expression_bit)
add_subdirectory(sc_expression_logical)
add_subdirectory(sc_statement)
add_subdirectory(sc_statement_ctrl)
add_subdirectory(sql)
add_subdirectory(sql_ddl)
add_subdirectory(sql_dml)
add_subdirectory(sql_dml_parts)
add_subdirectory(sql_expression)
add_subdirectory(sql_join_parts)

message(STATUS "src_smartcontract : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract top_src_smartcontract)
