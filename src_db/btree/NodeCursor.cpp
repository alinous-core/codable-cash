/*
 * NodeCursor.cpp
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#include "btree/NodeCursor.h"
#include "btree/NodeHandle.h"
#include "btree/AbstractBtreeKey.h"

namespace alinous {

NodePosition::NodePosition(NodeHandle* nodeHandle) {
	this->node = nodeHandle;
	this->pos = 0;
	this->innerNodes = nullptr;
	this->innerCount = 0;
}

NodePosition::~NodePosition() {
	delete this->node;

	if(this->innerNodes != nullptr){
		this->innerNodes->deleteElements();
		delete this->innerNodes;
	}
}

bool NodePosition::isLeaf() const {
	return this->node->isLeaf();
}

void NodePosition::loadInnerNodes(BtreeStorage* store) {
	RawArrayPrimitive<uint64_t>* fopsList = this->node->getInnerNodeFpos();
	this->innerNodes = new ArrayList<NodeHandle>(fopsList->size());

}

/****************************************************************************************/

NodeCursor::NodeCursor(NodeHandle* rootNode, BtreeStorage* store, int nodeNumber) {
	this->nodestack = new ArrayList<NodePosition>();
	NodePosition* npos = new NodePosition(rootNode);
	push(npos);

	this->nodeNumber = nodeNumber;
}

NodeCursor::~NodeCursor() {
	int maxLoop = this->nodestack->size();
	for(int i = 0; i != maxLoop; ++i){
		NodePosition* n = this->nodestack->get(i);
		delete n;
	}


	delete this->nodestack;
}

NodePosition* NodeCursor::pop() noexcept {
	int index = this->nodestack->size() - 1;
	NodePosition* node = this->nodestack->get(index);

	this->nodestack->remove(index);

	return node;
}

void NodeCursor::push(NodePosition* node) noexcept {
	this->nodestack->addElement(node);
}

NodePosition* NodeCursor::top() noexcept {
	int index = this->nodestack->size() - 1;
	return this->nodestack->get(index);
}

void NodeCursor::insert(AbstractBtreeKey* key, IBlockObject* data) {
	NodePosition* current = top();

	// down to leaf node
	while(!current->isLeaf()){

	}

	// check data nodes
	// 1. already has key

	// 2. Add key, then check whether the node is full or not

}



} /* namespace alinous */


