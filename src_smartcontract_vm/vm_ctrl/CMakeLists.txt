

set(__src
	AbstractCtrlInstruction.cpp
	ExecControlManager.cpp
	ReturnControl.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm_ctrl)

