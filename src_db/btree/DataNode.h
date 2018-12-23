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

class DataNode: public AbstractTreeNode {
public:
	DataNode();
	virtual ~DataNode();

	virtual bool isLeaf() const { return true; }
	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);
};

} /* namespace alinous */

#endif /* BTREE_DATANODE_H_ */
