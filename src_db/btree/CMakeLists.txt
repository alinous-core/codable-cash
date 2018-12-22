
set(__src
	AbstractTreeNode.cpp
	Btree.cpp
	BtreeConfig.cpp
	BtreeStorage.cpp
	DataNode.cpp
	TreeNode.cpp
)
handle_sub(codablecashlib "${__src}" db btree)
