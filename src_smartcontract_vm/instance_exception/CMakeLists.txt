

set(__src
	AbstractProgramException.cpp
	ZeroDivisionException.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_exception)

