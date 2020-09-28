
set(__src
	AbstractMemoryTreeNode.cpp
	BtreeOnMemory.cpp
	MemoryBtreeScanner.cpp
	MemoryDataNode.cpp
	MemoryNodeCursor.cpp
	MemoryNodeHandle.cpp
	MemoryTreeNode.cpp
)
handle_sub(codablecashlib "${__src}" db btree_memory)
