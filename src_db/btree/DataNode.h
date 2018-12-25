/*
 * DataNode.h
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#ifndef BTREE_DATANODE_H_
#define BTREE_DATANODE_H_

#include "btree/AbstractTreeNode.h"

namespace alinous {

class BTreeKeyFactory;
class AbstractBtreeKey;

class DataNode: public AbstractTreeNode {
public:
	explicit DataNode(AbstractBtreeKey* key);
	virtual ~DataNode();

	virtual bool isData() const { return true; }
	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);
	static DataNode* fromBinary(ByteBuffer* in, BTreeKeyFactory* factory);
};

} /* namespace alinous */

#endif /* BTREE_DATANODE_H_ */
