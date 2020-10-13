
set(__dirsrc "")

# import source codes
add_subdirectory(ext_arguments)
add_subdirectory(ext_binary)
add_subdirectory(instance)
add_subdirectory(instance/instance_array)
add_subdirectory(instance/instance_dom)
add_subdirectory(instance/instance_exception)
add_subdirectory(instance/instance_exception_class)
add_subdirectory(instance/instance_gc)
add_subdirectory(instance/instance_parts)
add_subdirectory(instance/instance_ref)
add_subdirectory(instance/instance_ref_class_static)
add_subdirectory(instance/instance_ref_class_static_meta)
add_subdirectory(instance/instance_ref_static)
add_subdirectory(instance/instance_string)
add_subdirectory(instance/reserved_classes)
add_subdirectory(instance/reserved_classes_string)
add_subdirectory(vm)
add_subdirectory(vm/memory)
add_subdirectory(vm/stack)
add_subdirectory(vm/type_check)
add_subdirectory(vm/variable_access)
add_subdirectory(vm/vm_ctrl)
add_subdirectory(vm/vm_trx)


message(STATUS "src_smartcontract_vm : ${__dirsrc}")

set_parentv("${__dirsrc}" src_smartcontract_vm top_src_smartcontract_vm)
