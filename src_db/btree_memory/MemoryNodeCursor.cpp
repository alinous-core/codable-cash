/*
 * MemoryNodeCursor.cpp
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#include "btree_memory/MemoryNodeCursor.h"
#include "btree_memory/MemoryNodeHandle.h"
#include "btree_memory/MemoryDataNode.h"
#include "btree_memory/MemoryTreeNode.h"
#include "btree_memory/BTreeOnMemory.h"

#include "btree/AbstractBtreeKey.h"

#include "filestore_block/IBlockObject.h"

#include "base/StackRelease.h"

#include "btreekey/InfinityKey.h"

namespace alinous {

MemoryNodeCursor::MemoryNodeCursor(MemoryNodeHandle* rootNode, int nodeNumber, BTreeOnMemory* btree) {
	this->nodestack = new ArrayList<MemoryNodeHandle>();
	this->nodeNumber = nodeNumber;
	this->btree = btree;

	push(rootNode);
}

MemoryNodeCursor::~MemoryNodeCursor() {
	int maxLoop = this->nodestack->size();
	for(int i = 0; i != maxLoop; ++i){
		MemoryNodeHandle* n = this->nodestack->get(i);
		delete n;
	}

	delete this->nodestack;
}

void MemoryNodeCursor::insert(const AbstractBtreeKey* key, IBlockObject* data) {
	MemoryNodeHandle* current = top();

	while(!current->isLeaf()){
		current = current->getNextChild(key);
		push(current);
	}

	// 1. already has key
	AbstractMemoryTreeNode* node = current->hasKey(key);
	if(node != nullptr){
		MemoryDataNode* dnode = dynamic_cast<MemoryDataNode*>(node);
		dnode->setData(data);
		return;
	}

	// 2. Add key, then check whether the node is full or not
	if(current->isFull(this->nodeNumber)){
		splitLeafNode(key, data);
		return;
	}


	// simply add data
	MemoryDataNode* dnode = new MemoryDataNode(key->clone());
	dnode->setData(data);
	current->addNode(dnode);
}

void MemoryNodeCursor::splitLeafNode(const AbstractBtreeKey* key, IBlockObject* data) {
	MemoryNodeHandle* current = top();

	MemoryDataNode* dataNode = new MemoryDataNode(key->clone());
	dataNode->setData(data);

	// split node
	ArrayList<AbstractMemoryTreeNode>* list = current->getInnerNodes();

	ArrayList<AbstractMemoryTreeNode> list1(this->nodeNumber);
	ArrayList<AbstractMemoryTreeNode> list2(this->nodeNumber);

	AbstractBtreeKey* newKey = setupTwoLists(list, dataNode, &list1, &list2);
	StackRelease<AbstractBtreeKey> __st_newkey(newKey);

	// new Node
	MemoryTreeNode* newNode = new MemoryTreeNode(this->nodeNumber, newKey->clone(), true);
	newNode->updateInnerNodes(&list1);

	// update current
	bool isroot = current->isRoot();
	current->setRoot(false);
	current->updateInnerNodes(&list2);

	// add to parent node
	if(isroot){
		createNewRoot(newNode);
	}
	else{
		addToParent(newNode);
	}
}

void MemoryNodeCursor::createNewRoot(MemoryTreeNode* newNode) {
	MemoryNodeHandle* current = top();

	MemoryTreeNode* rootNode = new MemoryTreeNode(true, this->nodeNumber, new InfinityKey(), false);
	rootNode->addNode(newNode);
	rootNode->addNode(current->getNode());

	this->btree->setRoot(rootNode);
}

void MemoryNodeCursor::addToParent(MemoryTreeNode* newNode) {
	pop();
	MemoryNodeHandle* current = top();

	if(current->isFull(this->nodeNumber)){
		splitTreeNode(newNode);
	}
	else{
		current->addNode(newNode);
	}
}

void MemoryNodeCursor::splitTreeNode(MemoryTreeNode* node) {
	MemoryNodeHandle* current = top();

	// split
	ArrayList<AbstractMemoryTreeNode>* list = current->getInnerNodes();

	ArrayList<AbstractMemoryTreeNode> list1(this->nodeNumber);
	ArrayList<AbstractMemoryTreeNode> list2(this->nodeNumber);

	AbstractBtreeKey* newKey = setupTwoLists(list, node, &list1, &list2);
	StackRelease<AbstractBtreeKey> __st_newkey(newKey);

	// new Node
	MemoryTreeNode* newNode = new MemoryTreeNode(this->nodeNumber, newKey->clone(), false);
	newNode->updateInnerNodes(&list1);

	// update current
	bool isroot = current->isRoot();
	current->setRoot(false);
	current->updateInnerNodes(&list2);

	// add to parent node
	if(isroot){
		createNewRoot(newNode);
	}
	else{
		addToParent(newNode);
	}
}

AbstractBtreeKey* MemoryNodeCursor::setupTwoLists(
		ArrayList<AbstractMemoryTreeNode>* list, AbstractMemoryTreeNode* node,
		ArrayList<AbstractMemoryTreeNode>* list1,
		ArrayList<AbstractMemoryTreeNode>* list2) {
	ArrayList<AbstractMemoryTreeNode> allList(list->size() + 1);

	AbstractBtreeKey* key = node->getKey();
	bool done = false;
	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractMemoryTreeNode* nh = list->get(i);

		if(!done){
			AbstractBtreeKey* nhKey = nh->getKey();
			if(nhKey->compareTo(key) > 0){
				done = true;
				allList.addElement(node);
			}
		}

		allList.addElement(nh);
	}

	if(!done){
		allList.addElement(node);
	}

	int total = allList.size();
	int list1Size = total / 2;

	int i = 0;
	for(; i != list1Size; ++i){
		AbstractMemoryTreeNode* n = allList.get(i);
		list1->addElement(n);
	}
	for(; i != total; ++i){
		AbstractMemoryTreeNode* n = allList.get(i);
		list2->addElement(n);
	}

	return allList.get(list1Size - 1)->getKey()->clone();
}

IBlockObject* MemoryNodeCursor::gotoFirst() noexcept {
	MemoryNodeHandle* current = top();

	while(!current->isLeaf()){
		AbstractMemoryTreeNode* n = current->nextNode();

		current = new MemoryNodeHandle(n);
		push(current);
	}

	AbstractMemoryTreeNode* node = current->nextNode();
	push(new MemoryNodeHandle(node));

	MemoryDataNode* dataNode = dynamic_cast<MemoryDataNode*>(node);
	IBlockObject* obj = dataNode->getData();

	return obj;
}

IBlockObject* MemoryNodeCursor::gotoKey(const AbstractBtreeKey* key) noexcept {
	gotoLeaf(key);

	MemoryNodeHandle* current = top();

	MemoryNodeHandle* next = current->gotoEqMoreThanKey(key);
	if(next == nullptr){
		return nullptr;
	}

	push(next);

	AbstractMemoryTreeNode* node = next->getNode();
	MemoryDataNode* dataNode = dynamic_cast<MemoryDataNode*>(node);
	IBlockObject* obj = dataNode->getData();

	return obj;
}

IBlockObject* MemoryNodeCursor::getNext() noexcept {
	// pop data node
	pop();

	// find leaf
	MemoryNodeHandle* current = top();
	while(!current->isLeaf() || !current->hasNext()){
		AbstractMemoryTreeNode* n = current->nextNode();

		if(n == nullptr){
			if(current->isRoot()){
				return nullptr;
			}

			pop();
			current = top();
		}
		else{
			current = new MemoryNodeHandle(n);
			push(current);
		}
	}

	// current is leaf having next data
	AbstractMemoryTreeNode* node = current->nextNode();
	push(new MemoryNodeHandle(node));

	MemoryDataNode* dataNode = dynamic_cast<MemoryDataNode*>(node);
	IBlockObject* obj = dataNode->getData();

	return obj;
}

MemoryNodeHandle* MemoryNodeCursor::gotoLeaf(const AbstractBtreeKey* key) {
	MemoryNodeHandle* current = top();

	while(!current->isLeaf()){
		MemoryNodeHandle* nextNode = current->getNextChild(key);

		push(nextNode);
		current = nextNode;
	}

	return current;
}

void MemoryNodeCursor::pop() noexcept {
	int index = this->nodestack->size() - 1;
	MemoryNodeHandle* nodeHandle = this->nodestack->get(index);

	this->nodestack->remove(index);

	delete nodeHandle;
}

void MemoryNodeCursor::push(MemoryNodeHandle* node) noexcept {
	this->nodestack->addElement(node);
}

MemoryNodeHandle* MemoryNodeCursor::top() noexcept {
	int index = this->nodestack->size() - 1;
	return this->nodestack->get(index);
}

} /* namespace alinous */
