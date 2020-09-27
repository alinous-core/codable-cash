/*
 * TreeNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_TREENODE_H_
#define BTREE_TREENODE_H_

#include "btree/AbstractTreeNode.h"
#include "base/ArrayList.h"
#include "base/RawArrayPrimitive.h"

#include <cstdint>

namespace alinous {

class AbstractBtreeKey;
class BtreeKeyFactory;

class TreeNode: public AbstractTreeNode {
private:
	TreeNode &operator=(const TreeNode &o) = delete;

	TreeNode();
public:
	TreeNode(const TreeNode& inst);
	explicit TreeNode(int numChildren, AbstractBtreeKey* key, bool reaf);
	explicit TreeNode(bool isroot, int numChildren, AbstractBtreeKey* key, bool reaf);
	virtual ~TreeNode();

	virtual bool isData() const noexcept { return false; }

	bool isRoot() const noexcept;
	void setIsRoot(bool isroot) noexcept;
	bool isLeaf() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static TreeNode* fromBinary(ByteBuffer* in, BtreeKeyFactory* factory);

	virtual RawArrayPrimitive<uint64_t>* getInnerNodeFpos() const;
	void updateInnerNodeFpos(const RawArrayPrimitive<uint64_t>* newlist) noexcept;

	virtual IBlockObject* copyData() const noexcept;

private:
	bool root;
	bool leaf;
	RawArrayPrimitive<uint64_t>* children;
};

} /* namespace alinous */

#endif /* BTREE_TREENODE_H_ */
