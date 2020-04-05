

set(__src
	AbstractCtrlInstruction.cpp
	BlockState.cpp
	ExecControlManager.cpp
	ReturnControl.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm_ctrl)

