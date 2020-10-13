

set(__src
	AbstractDomInstance.cpp
	DomArrayVariable.cpp
	DomRuntimeReference.cpp
	DomVariableInstance.cpp
	DomVariableReference.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm instance/instance_dom)

