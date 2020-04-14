

set(__src
	ExceptionClassDeclare.cpp
	ExceptionInstanceFactory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_exception_class)

