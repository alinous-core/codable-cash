
set(__src
	BTreeOnMemory.cpp
	MemoryNodeHandle.cpp
	MemoryTreeNode.cpp
)
handle_sub(codablecashlib "${__src}" db btree_memory)
