/*
 * AbstractTreeNode.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/AbstractTreeNode.h"
#include "btree/AbstractBtreeKey.h"

#include "base_io/ReverseByteBuffer.h"

namespace alinous {

AbstractTreeNode::AbstractTreeNode(AbstractBtreeKey* key) : IBlockObject() {
	this->key = key;
	this->fpos = 0;
}

AbstractTreeNode::~AbstractTreeNode() {
	delete this->key;
}

int AbstractTreeNode::binarySize() {
	int size = this->key->binarySize();
	size += sizeof(this->fpos);

	return size;
}

void AbstractTreeNode::toBinary(ByteBuffer* out) {
	this->key->toBinary(out);
	out->putLong(this->fpos);
}

} /* namespace alinous */
