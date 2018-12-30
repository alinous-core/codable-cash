/*
 * NodePosition.cpp
 *
 *  Created on: 2018/12/29
 *      Author: iizuka
 */

#include "btree/NodePosition.h"
#include "btree/NodeHandle.h"
#include "btree/AbstractTreeNode.h"
#include "btree/AbstractBtreeKey.h"
#include "btree/BtreeStorage.h"
#include "btree/NodeCacheRef.h"
#include "btree/TreeNode.h"
#include "btree/exceptions.h"

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
		clearCache();
	}
}

void NodePosition::clearCache() {
	this->innerNodes->deleteElements();
	delete this->innerNodes, this->innerNodes = nullptr;

}

uint64_t NodePosition::getFpos() const noexcept {
	return this->node->getRef()->getNode()->getFpos();
}

bool NodePosition::isLeaf() const {
	return this->node->isLeaf();
}

bool NodePosition::isRoot() const {
	return this->node->isRoot();
}

void NodePosition::setRoot(bool isroot) {
	this->node->setIsRoot(isroot);
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
	clearCache();
}

uint64_t NodePosition::getNextChild(const AbstractBtreeKey* key) const {
	uint64_t ret = 0;
	int maxLoop = this->innerCount;
	for(int i = 0; i != maxLoop; ++i){
		NodeHandle* nh = this->innerNodes->get(i);

		if(key->compareTo(nh->getKey()) < 0){
			ret = nh->getRef()->getNode()->getFpos();
			break;
		}
	}

	return ret;
}

ArrayList<NodeHandle>* NodePosition::getInnerNodes() const noexcept {
	return this->innerNodes;
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

void NodePosition::updateInnerNodeFpos(const RawArrayPrimitive<uint64_t>* newlist) {
	TreeNode* treeNode = this->node->toTreeNode();
	treeNode->updateInnerNodeFpos(newlist);

	clearCache();
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

NodeHandle* NodePosition::getNodeHandle() const noexcept {
	return this->node;
}


} /* namespace alinous */

