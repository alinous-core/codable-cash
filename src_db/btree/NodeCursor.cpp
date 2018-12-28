/*
 * NodeCursor.cpp
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#include "btree/NodeCursor.h"
#include "btree/NodeHandle.h"
#include "btree/AbstractTreeNode.h"
#include "btree/TreeNode.h"
#include "btree/AbstractBtreeKey.h"
#include "btree/BtreeStorage.h"
#include "btree/NodeCacheRef.h"
#include "btree/exceptions.h"

#include "btree/DataNode.h"

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

NodeHandle* NodePosition::hasKey(const AbstractBtreeKey* key) const {
	int maxLoop = this->innerNodes->size();
	for(int i = 0; i != maxLoop; ++i){
		NodeHandle* nodeHandle = this->innerNodes->get(i);
		if(nodeHandle == nullptr){
			return nullptr;
		}
		AbstractBtreeKey* inkey = nodeHandle->getRef()->getNode()->getKey();
		if(key->compareTo(inkey) == 0){
			return nodeHandle;
		}
	}

	return nullptr;
}

void NodePosition::loadInnerNodes(BtreeStorage* store) {
	RawArrayPrimitive<uint64_t>* fposList = this->node->getInnerNodeFpos();
	this->innerNodes = new ArrayList<NodeHandle>(fposList->size());

	this->innerCount = 0;

	int maxLoop = fposList->size();
	for(int i = 0; i != maxLoop; ++i){
		uint64_t fpos = fposList->get(i);
		if(fpos == 0){
			this->innerNodes->addElement(nullptr);
			continue;
		}

		NodeHandle* nodeHandle = store->loadNode(fpos);
		checkNoNull(nodeHandle, __FILE__, __LINE__);

		this->innerNodes->addElement(nodeHandle);
		this->innerCount++;
	}
}

bool NodePosition::isFull(int nodeNumber) const noexcept {
	return this->innerCount >= nodeNumber;
}

void NodePosition::addNode(const AbstractBtreeKey* key, uint64_t fpos, int nodeNumber) {
	for(int i = 0; i != nodeNumber; ++i){
		NodeHandle* nh = this->innerNodes->get(i);

		if(nh == nullptr || nh->getKey()->compareTo(key) > 0){
			internalAddNode(i, fpos);
			break;
		}
	}
}

void NodePosition::internalAddNode(int index, uint64_t fpos) {
	TreeNode* treeNode = this->node->toTreeNode();
	RawArrayPrimitive<uint64_t>* list = treeNode->getInnerNodeFpos();

	int first = list->size() - 1;
	for(int i = first; i > index; --i){
		uint64_t f = list->get(i - 1);
		list->set(i ,f);
	}
	list->set(index ,fpos);

	this->innerCount++;
}

void NodePosition::save(BtreeStorage* store) {
	AbstractTreeNode* node = this->node->getRef()->getNode();

	store->updateNode(node);
}

void NodePosition::checkNoNull(NodeHandle* nodeHandle, const char* srcfile, int srcline) noexcept(false) {
	if(nodeHandle == nullptr){
		throw new NodeStructureException(srcfile, srcline);
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

void NodeCursor::insert(const AbstractBtreeKey* key, const IBlockObject* data) {
	NodePosition* current = top();

	// check data nodes
	current->loadInnerNodes(this->store);

	// down to leaf node
	while(!current->isLeaf()){

	}

	// 1. already has key
	NodeHandle* sameKeyDataNode = current->hasKey(key);
	if(sameKeyDataNode != nullptr){
		uint64_t dataFpos = this->store->storeData(data);

		DataNode* dnode = sameKeyDataNode->toDataNode();
		dnode->getInnerNodeFpos()->addElement(dataFpos, 0);

		this->store->updateNode(dnode);

		return;
	}

	// 2. Add key, then check whether the node is full or not
	if(current->isFull(this->nodeNumber)){

		return;
	}

	// simply add data
	uint64_t dataFpos = this->store->storeData(data);

	DataNode dataNode(key->clone());
	dataNode.getInnerNodeFpos()->addElement(dataFpos, 0);

	uint64_t newDataNodeFpos = this->store->storeNode(&dataNode);

	current->addNode(key, newDataNodeFpos, this->nodeNumber);
	current->save(this->store);
}



} /* namespace alinous */


