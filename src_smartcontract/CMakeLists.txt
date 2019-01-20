
set(__dirsrc "")

# import source codes
add_subdirectory(compiler)
add_subdirectory(sc)
add_subdirectory(sc_declare)
add_subdirectory(sc_declare_types)
add_subdirectory(sc_statement)


message(STATUS "src_smartcontract : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract top_src_smartcontract)
