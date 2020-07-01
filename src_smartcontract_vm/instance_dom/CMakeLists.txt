

set(__src
	AbstractDomInstance.cpp
	DomRuntimeReference.cpp
	DomVariableInstance.cpp
	DomVariableReference.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance_dom)

