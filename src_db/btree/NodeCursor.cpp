/*
 * NodeCursor.cpp
 *
 *  Created on: 2018/12/26
 *      Author: iizuka
 */

#include "btree/NodeCursor.h"
#include "btree/NodePosition.h"
#include "btree/NodeHandle.h"
#include "btree/AbstractTreeNode.h"
#include "btree/TreeNode.h"
#include "btree/AbstractBtreeKey.h"
#include "btree/BtreeStorage.h"
#include "btree/NodeCacheRef.h"
#include "btree/exceptions.h"

#include "btree/DataNode.h"

#include "base/StackRelease.h"

namespace alinous {


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
		splitLeafNode(key, data);
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

void NodeCursor::splitLeafNode(const AbstractBtreeKey* key, const IBlockObject* data) {
	NodePosition* current = top();

	// data node
	uint64_t dataFpos = this->store->storeData(data);
	DataNode dataNode(key->clone());
	dataNode.getInnerNodeFpos()->addElement(dataFpos, 0);

	uint64_t newDataNodeFpos = this->store->storeNode(&dataNode);

	// split
	ArrayList<NodeHandle>* list = current->getInnerNodes();

	RawArrayPrimitive<uint64_t> list1(this->nodeNumber);
	RawArrayPrimitive<uint64_t> list2(this->nodeNumber);

	AbstractBtreeKey* newKey = setupTwoLists(list, &dataNode, &list1, &list2);
	StackRelease<AbstractBtreeKey> __st_newkey(newKey);

	// new Node
	TreeNode newNode(this->nodeNumber, newKey->clone(), true);
	newNode.updateInnerNodeFpos(&list1);
	this->store->storeNode(&newNode);

	// TODO: update newNode & current
	bool isroot = current->isRoot();
	current->setRoot(false);


	// add to parent node
	if(isroot){

	}
	else{

	}
}

AbstractBtreeKey* NodeCursor::setupTwoLists(ArrayList<NodeHandle>* list, AbstractTreeNode* node,
								RawArrayPrimitive<uint64_t>* list1, RawArrayPrimitive<uint64_t>* list2) {
	ArrayList<AbstractTreeNode> allList(list->size() + 1);

	AbstractBtreeKey* key = node->getKey();
	bool done = false;
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		NodeHandle* nh = list->get(i);
		assert(nh != nullptr);

		if(!done){
			AbstractBtreeKey* nhKey = nh->getKey();
			if(nhKey->compareTo(key) > 0){
				done = true;
				allList.addElement(node);
			}
		}

		AbstractTreeNode* nhnode = nh->getRef()->getNode();
		allList.addElement(nhnode);
	}

	// it does not come here
	//if(!done){
	//	allList.addElement(node);
	//}
	assert(done);

	int total = allList.size();
	int list1Size = total / 2;

	int i = 0;
	for(; i != list1Size; ++i){
		AbstractTreeNode* n = allList.get(i);
		list1->addElement(n->getFpos());
	}
	for(; i != total; ++i){
		AbstractTreeNode* n = allList.get(i);
		list2->addElement(n->getFpos());
	}

	return allList.get(list1Size - 1)->getKey()->clone();
}

} /* namespace alinous */


