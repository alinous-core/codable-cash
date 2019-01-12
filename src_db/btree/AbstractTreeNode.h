/*
 * AbstractTreeNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_ABSTRACTTREENODE_H_
#define BTREE_ABSTRACTTREENODE_H_

#include "filestore_block/IBlockObject.h"
#include <inttypes.h>
#include "base/RawArrayPrimitive.h"

namespace alinous {

class AbstractBtreeKey;
class BtreeKeyFactory;
class DataNode;
class TreeNode;

class AbstractTreeNode : IBlockObject {
public:
	static const constexpr char NODE{0x01};
	static const constexpr char DATA{0x02};

	explicit AbstractTreeNode(AbstractBtreeKey* key);
	virtual ~AbstractTreeNode();

	virtual bool isData() const = 0;
	AbstractBtreeKey* getKey() const noexcept {
		return this->key;
	}

	uint64_t getFpos() const noexcept {
		return fpos;
	}
	void setFpos(uint64_t fpos) noexcept {
		this->fpos = fpos;
	}

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	void fromBinaryAbstract(ByteBuffer* in, BtreeKeyFactory* factory);

	static DataNode* toDataNode(AbstractTreeNode* node);
	static TreeNode* toTreeNode(AbstractTreeNode* node);

protected:
	AbstractBtreeKey* key;
	uint64_t fpos;
};

} /* namespace alinous */

#endif /* BTREE_ABSTRACTTREENODE_H_ */
