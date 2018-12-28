/*
 * DataNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_DATANODE_H_
#define BTREE_DATANODE_H_

#include "btree/AbstractTreeNode.h"

#include "base/RawArrayPrimitive.h"

namespace alinous {

class BTreeKeyFactory;
class AbstractBtreeKey;

class DataNode: public AbstractTreeNode {
public:
	DataNode();
	explicit DataNode(int numChildren, AbstractBtreeKey* key);
	virtual ~DataNode();

	virtual bool isData() const { return true; }
	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static DataNode* fromBinary(ByteBuffer* in, BTreeKeyFactory* factory);

	virtual RawArrayPrimitive<uint64_t>* getInnerNodeFpos() const;

private:
	RawArrayPrimitive<uint64_t>* children;
};

} /* namespace alinous */

#endif /* BTREE_DATANODE_H_ */
