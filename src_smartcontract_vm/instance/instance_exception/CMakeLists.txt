

set(__src
	ArrayOutOfBoundsExceptionClassDeclare.cpp
	ExceptionInterrupt.cpp
	NullPointerExceptionClassDeclare.cpp
	TypeCastExceptionClassDeclare.cpp
	ZeroDivisionExceptionClassDeclare.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_exception)

