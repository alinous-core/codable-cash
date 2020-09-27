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

DataNode::DataNode(const DataNode& inst) : AbstractTreeNode(inst.key->clone()) {
	this->fpos = inst.fpos;
	this->datafpos = inst.datafpos;
}

DataNode::DataNode() : AbstractTreeNode(nullptr) {
	this->datafpos = 0L;
}

DataNode::DataNode(AbstractBtreeKey* key) : AbstractTreeNode(key) {
	this->datafpos = 0L;
}

DataNode::~DataNode() {

}

int DataNode::binarySize() const {
	int size = sizeof(char); // nodetype

	size += AbstractTreeNode::binarySize(); // key + fpos...

	size += sizeof(uint64_t); // data fpos

	return size;
}

void DataNode::toBinary(ByteBuffer* out) const {
	out->put(AbstractTreeNode::DATA); // nodetype

	AbstractTreeNode::toBinary(out); // key + fpos...

	out->putLong(this->datafpos);
}

DataNode* DataNode::fromBinary(ByteBuffer* in, BtreeKeyFactory* factory) {
	DataNode* node = new DataNode();

	node->fromBinaryAbstract(in, factory);
	node->datafpos = in->getLong();

	return node;
}

uint64_t DataNode::getDataFpos() const noexcept {
	return this->datafpos;
}

void DataNode::setDataFpos(uint64_t fpos) noexcept {
	this->datafpos = fpos;
}

IBlockObject* DataNode::copyData() const noexcept {
	return new DataNode(*this);
}


} /* namespace alinous */
