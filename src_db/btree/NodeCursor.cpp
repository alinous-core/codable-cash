/*
 * NodeCursor.cpp
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#include "btree/NodeCursor.h"
#include "btree/NodeHandle.h"
#include "btree/AbstractTreeNode.h"
#include "btree/AbstractBtreeKey.h"
#include "btree/BtreeStorage.h"
#include "btree/NodeCacheRef.h"

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

bool NodePosition::hasKey(AbstractBtreeKey* key) const {
	int maxLoop = this->innerNodes->size();
	for(int i = 0; i != maxLoop; ++i){
		NodeHandle* nodeHandle = this->innerNodes->get(i);
		if(nodeHandle == nullptr){
			return false;
		}
		AbstractBtreeKey* inkey = nodeHandle->getRef()->getNode()->getKey();
		if(key->compareTo(inkey)){
			return true;
		}
	}

	return false;
}

void NodePosition::loadInnerNodes(BtreeStorage* store) {
	RawArrayPrimitive<uint64_t>* fposList = this->node->getInnerNodeFpos();
	this->innerNodes = new ArrayList<NodeHandle>(fposList->size());

	int maxLoop = fposList->size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t fpos = fposList->get(i);
		if(fpos == 0){
			this->innerNodes->addElement(nullptr);
			continue;
		}

		NodeHandle* nodeHandle = store->loadNode(fpos);
		this->innerNodes->addElement(nodeHandle);
	}
}

/****************************************************************************************/

NodeCursor::NodeCursor(NodeHandle* rootNode, BtreeStorage* store, int nodeNumber) {
	this->nodestack = new ArrayList<NodePosition>();
	NodePosition* npos = new NodePosition(rootNode);
	push(npos);

	this->store = store;
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

	// check data nodes
	current->loadInnerNodes(this->store);

	// down to leaf node
	while(!current->isLeaf()){

	}

	// 1. already has key
	if(current->hasKey(key)){
		return;
	}

	// 2. Add key, then check whether the node is full or not

}



} /* namespace alinous */


