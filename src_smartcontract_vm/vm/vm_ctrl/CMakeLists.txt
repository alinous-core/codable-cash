

set(__src
	AbstractCtrlInstruction.cpp
	BlockState.cpp
	BreakControl.cpp
	ContinueControl.cpp
	ExceptionControl.cpp
	ExecControlManager.cpp
	ReturnControl.cpp
)
handle_sub(codablecashlib "${__src}" smartcontract_vm vm/vm_ctrl)

