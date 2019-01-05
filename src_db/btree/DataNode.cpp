/*
 * DataNode.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/DataNode.h"
#include "btree/AbstractBtreeKey.h"
#include "base_io/ReverseByteBuffer.h"

namespace alinous {

DataNode::DataNode() : AbstractTreeNode(nullptr) {
	this->children = nullptr;
}

DataNode::DataNode(AbstractBtreeKey* key) : AbstractTreeNode(key) {
	this->children = new RawArrayPrimitive<uint64_t>(8);
}

DataNode::~DataNode() {
	delete this->children;
}

int DataNode::binarySize() const {
	int size = sizeof(char); // nodetype

	size += AbstractTreeNode::binarySize(); // key + fpos...

	size += sizeof(int32_t); // number of children
	size += sizeof(uint64_t) * this->children->size();

	return size;
}

void DataNode::toBinary(ByteBuffer* out) const {
	out->put(AbstractTreeNode::DATA); // nodetype

	AbstractTreeNode::toBinary(out); // key + fpos...

	int maxLoop = this->children->size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint64_t nodefpos = this->children->get(i);
		out->putLong(nodefpos);
	}
}

DataNode* DataNode::fromBinary(ByteBuffer* in, BtreeKeyFactory* factory) {
	DataNode* node = new DataNode();

	node->fromBinaryAbstract(in, factory);

	int maxLoop = in->getInt();
	node->children = new RawArrayPrimitive<uint64_t>(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		uint64_t nodefpos = in->getLong();
		node->children->addElement(nodefpos);
	}

	return node;
}

RawArrayPrimitive<uint64_t>* DataNode::getInnerNodeFpos() const {
	return this->children;
}

} /* namespace alinous */


