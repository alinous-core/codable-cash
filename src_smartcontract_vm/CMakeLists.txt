
set(__dirsrc "")

# import source codes
add_subdirectory(vm)


message(STATUS "src_smartcontract_vm : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract_vm top_src_smartcontract_vm)
