
set(__src
	AbstractBtreeKey.cpp
	AbstractTreeNode.cpp
	Btree.cpp
	BtreeHeaderBlock.cpp
	BtreeConfig.cpp
	BtreeStorage.cpp
	DataNode.cpp
	NodeCache.cpp
	NodeCacheRef.cpp
	NodeHandle.cpp
	TreeNode.cpp
)
handle_sub(codablecashlib "${__src}" db btree)
