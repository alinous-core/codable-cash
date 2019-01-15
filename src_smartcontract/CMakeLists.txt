
set(__dirsrc "")

# import source codes
add_subdirectory(sc)
add_subdirectory(sc_declare)


message(STATUS "src_smartcontract : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract top_src_smartcontract)
