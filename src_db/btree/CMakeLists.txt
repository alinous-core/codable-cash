
set(__src
	AbstractBtreeDataFactory.cpp
	AbstractBtreeKey.cpp
	AbstractTreeNode.cpp
	Btree.cpp
	BtreeHeaderBlock.cpp
	BtreeScanner.cpp
	BtreeConfig.cpp
	BtreeStorage.cpp
	DataNode.cpp
	exceptions.cpp
	IBtreeScanner.cpp
	NodeCursor.cpp
	NodeHandle.cpp
	NodePosition.cpp
	TreeNode.cpp
)
handle_sub(codablecashlib "${__src}" db btree)
