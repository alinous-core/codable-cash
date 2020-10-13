

set(__src
	AbstractExceptionClassDeclare.cpp
	ExceptionClassDeclare.cpp
	ExceptionInstanceFactory.cpp
	VmExceptionInstance.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_exception_class)

