/*
 * NodeCache.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btree/NodeCache.h"
#include "btree/AbstractTreeNode.h"

namespace alinous {

NodeCache::NodeCache(int numDataBuffer, int numNodeBuffer) {
	this->numDataBuffer = numDataBuffer;
	this->numNodeBuffer = numNodeBuffer;

	this->nodes = new RawLinkedList<AbstractTreeNode>();
	this->datas = new RawLinkedList<AbstractTreeNode>();

}

NodeCache::~NodeCache() {

}

} /* namespace alinous */
