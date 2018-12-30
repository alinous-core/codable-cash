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
#include "btreekey/InfinityKey.h"

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
		uint64_t nextFpos = current->getNextChild(key);
		NodeHandle* nh = this->store->loadNode(nextFpos);

		current = new NodePosition(nh);
		push(current);

		current->loadInnerNodes(this->store);
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

	current->loadInnerNodes(this->store);
}

void NodeCursor::splitLeafNode(const AbstractBtreeKey* key, const IBlockObject* data) {
	NodePosition* current = top();

	// data node
	uint64_t dataFpos = this->store->storeData(data);
	DataNode dataNode(key->clone());
	dataNode.getInnerNodeFpos()->addElement(dataFpos, 0);

	this->store->storeNode(&dataNode);

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

	// update current
	bool isroot = current->isRoot();
	current->setRoot(false);
	current->updateInnerNodeFpos(&list2);
	current->save(this->store);

	// add to parent node
	if(isroot){
		createNewRoot(&newNode);
	}
	else{
		addToParent(&newNode);
	}
}

void NodeCursor::createNewRoot(TreeNode* newNode) {
	NodePosition* current = pop();
	StackRelease<NodePosition> _st_current(current);

	TreeNode rootNode(true, this->nodeNumber, new InfinityKey(), false);
	RawArrayPrimitive<uint64_t>* nodes = rootNode.getInnerNodeFpos();
	nodes->set(0, newNode->getFpos());
	nodes->set(1, current->getFpos());

	this->store->storeNode(&rootNode);

	this->store->updateRootFpos(rootNode.getFpos());
}

void NodeCursor::addToParent(TreeNode* newNode) {
	delete pop();

	NodePosition* current = top();

	if(current->isFull(this->nodeNumber)){
		splitTreeNode(newNode);
	}
	else{
		current->addNode(newNode->getKey(), newNode->getFpos(), this->nodeNumber);
		current->save(this->store);

		// reload
		current->loadInnerNodes(this->store);
	}
}

void NodeCursor::splitTreeNode(TreeNode* node) {
	NodePosition* current = top();

	// split
	ArrayList<NodeHandle>* list = current->getInnerNodes();

	RawArrayPrimitive<uint64_t> list1(this->nodeNumber);
	RawArrayPrimitive<uint64_t> list2(this->nodeNumber);

	AbstractBtreeKey* newKey = setupTwoLists(list, node, &list1, &list2);
	StackRelease<AbstractBtreeKey> __st_newkey(newKey);

	// new Node
	TreeNode newNode(this->nodeNumber, newKey->clone(), false);
	newNode.updateInnerNodeFpos(&list1);
	this->store->storeNode(&newNode);

	// update current
	bool isroot = current->isRoot();
	current->setRoot(false);
	current->updateInnerNodeFpos(&list2);
	current->save(this->store);

	// add to parent node
	if(isroot){
		createNewRoot(&newNode);
	}
	else{
		addToParent(&newNode);
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

	if(!done){
		allList.addElement(node);
	}

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

IBlockObject* NodeCursor::gotoFirst() {
	NodePosition* current = top();

	// check data nodes
	current->loadInnerNodes(this->store);

	while(!current->isLeaf()){
	//	uint64_t nextFpos = current->getInnerNodes()->get(0)->getFpos();
		uint64_t nextFpos = current->nextNode();
		NodeHandle* nh = this->store->loadNode(nextFpos);

		current = new NodePosition(nh);
		push(current);

		current->loadInnerNodes(this->store);
	}

	uint64_t nextFpos = current->nextNode();
	NodeHandle* nh = this->store->loadNode(nextFpos);
	current = new NodePosition(nh);
	push(current);

	checkIsDataNode(current->getNodeHandle(), __FILE__, __LINE__);

	uint64_t datafpos = current->nextData();

	return this->store->loadData(datafpos);
}

IBlockObject* NodeCursor::getNext() {
	NodePosition* current = top();

	// get data from current node;
	checkIsDataNode(current->getNodeHandle(), __FILE__, __LINE__);
	uint64_t dfpos = current->nextData();

	if(dfpos != 0){
		return this->store->loadData(dfpos);
	}

	// pop data node
	delete pop();

	current = top();
	while(!current->isLeaf() || !current->hasNext()){
		uint64_t nextfpos = current->nextNode();

		if(nextfpos == 0){
			if(current->isRoot()){
				return nullptr;
			}
			delete pop();
			current = top();
		}
		else{
			NodeHandle* nh = this->store->loadNode(nextfpos);
			current = new NodePosition(nh);
			push(current);

			current->loadInnerNodes(this->store);
		}
	}

	// current is leaf having next data
	uint64_t nextfpos = current->nextNode();
	NodeHandle* nh = this->store->loadNode(nextfpos);
	current = new NodePosition(nh);
	push(current);

	checkIsDataNode(current->getNodeHandle(), __FILE__, __LINE__);

	uint64_t datafpos = current->nextData();

	return this->store->loadData(datafpos);
}



void NodeCursor::checkIsDataNode(NodeHandle* nodeHandle, const char* srcfile, int srcline) {
	if(!nodeHandle->isData()){
		throw new NodeStructureException(srcfile, srcline);
	}
}

} /* namespace alinous */

