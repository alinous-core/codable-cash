

set(__src
	ArrayOutOfBoundsExceptionClassDeclare.cpp
	NullPointerExceptionClassDeclare.cpp
	ZeroDivisionExceptionClassDeclare.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_exception)

