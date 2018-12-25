/*
 * DataNode.cpp
 *
 *  Created on: 2018/12/18
 *      Author: iizuka
 */

#include "btree/DataNode.h"

namespace alinous {

DataNode::DataNode() : AbstractTreeNode(nullptr) {


}

DataNode::~DataNode() {

}

int DataNode::binarySize() {
	// TODO Auto-generated destructor stub
	return 0;
}

void DataNode::toBinary(ByteBuffer* out) {
	// TODO Auto-generated constructor stub
}

DataNode* DataNode::fromBinary(ByteBuffer* in, BTreeKeyFactory* factory) {
	// TODO Auto-generated constructor stub
	return nullptr;
}

} /* namespace alinous */
