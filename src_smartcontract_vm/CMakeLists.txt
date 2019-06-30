
set(__dirsrc "")

# import source codes
add_subdirectory(instance)
add_subdirectory(instance_gc)
add_subdirectory(instance_parts)
add_subdirectory(instance_ref)
add_subdirectory(memory)
add_subdirectory(stack)
add_subdirectory(vm)


message(STATUS "src_smartcontract_vm : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract_vm top_src_smartcontract_vm)
