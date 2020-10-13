

set(__src
	AbstractReservedClassDeclare.cpp
	ReservedClassRegistory.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/reserved_classes)

