
set(__src
	AbstractMemoryTreeNode.cpp
	BTreeOnMemory.cpp
	MemoryNodeCursor.cpp
	MemoryNodeHandle.cpp
	MemoryTreeNode.cpp
)
handle_sub(codablecashlib "${__src}" db btree_memory)
