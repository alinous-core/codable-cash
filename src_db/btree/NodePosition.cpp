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
#include "btree/DataNode.h"
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
	if(this->innerNodes != nullptr){
		this->innerNodes->deleteElements();
		delete this->innerNodes, this->innerNodes = nullptr;
	}
}

bool NodePosition::isEmpty() const noexcept {
	return this->innerCount == 0;
}

const AbstractBtreeKey* NodePosition::getKey() const noexcept {
	return this->node->getKey();
}

uint64_t NodePosition::getFpos() const noexcept {
	return this->node->getFpos();
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
/*
bool NodePosition::isData() const {
	return this->node->isData();
}
*/
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
	clearCache();

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

		if(key->compareTo(nh->getKey()) <= 0){
			ret = nh->getFpos();
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

uint64_t NodePosition::nextData() {
	DataNode* dnode = this->node->toDataNode();

	//if(0 < this->pos){
	//	return 0;
	//}
	assert(this->pos == 0);

	this->pos++;
	return dnode->getDataFpos();
}

uint64_t NodePosition::nextNode() {
	TreeNode* treeNode = this->node->toTreeNode();
	RawArrayPrimitive<uint64_t>* list = treeNode->getInnerNodeFpos();

	if(this->innerCount - 1 < this->pos){
		return 0;
	}

	int cur = this->pos++;
	return list->get(cur);
}

bool NodePosition::hasNext() {
	return this->innerCount > this->pos;
}

bool NodePosition::removeChildNode(const AbstractBtreeKey* key, BtreeStorage* store) {
	int removePos = indexof(key);
	if(removePos < 0){
		return false;
	}

	if(isLeaf()){
		internalRemoveLeafChildNode(removePos, store);
	}
	else{
		internalRemoveChildNode(removePos, store);
	}

	return true;
}

void NodePosition::removeInnerNodeFpos(int index) noexcept {
	RawArrayPrimitive<uint64_t>* dnodesList = this->node->getInnerNodeFpos();
	int maxLoop = this->innerCount - 1;
	int i = index;
	for(; i != maxLoop; i++){
		uint64_t nextfpos = dnodesList->get(i + 1);
		dnodesList->set(i, nextfpos);
	}

	dnodesList->set(i, 0);
}

void NodePosition::internalRemoveChildNode(int index, BtreeStorage* store) {
	// delete cache use count
	NodeHandle* nh = this->innerNodes->get(index);
	TreeNode* treeNode = nh->toTreeNode();

	this->innerNodes->remove(index);
	delete nh;

	// remove child node
	uint64_t nodeFpos = treeNode->getFpos();
	store->remove(nodeFpos);

	// update self
	removeInnerNodeFpos(index);
	this->innerCount--;
	store->updateNode(this->node->getRef()->getNode());
}

void NodePosition::internalRemoveLeafChildNode(int index, BtreeStorage* store) {
	// delete cache use count
	NodeHandle* nh = this->innerNodes->get(index);
	DataNode* dnode = nh->toDataNode();

	this->innerNodes->remove(index);
	delete nh;

	// remove data
	uint64_t dataFpos = dnode->getDataFpos();
	store->removeData(dataFpos);

	// remove child data node
	uint64_t nodeFpos = dnode->getFpos();
	store->remove(nodeFpos);

	// update self
	removeInnerNodeFpos(index);
	this->innerCount--;

	store->updateNode(this->node->getRef()->getNode());
}

int NodePosition::indexof(const AbstractBtreeKey* key) const {
	int maxLoop = this->innerCount;
	for(int i = 0; i != maxLoop; ++i){
		NodeHandle* nh = this->innerNodes->get(i);

		if(key->compareTo(nh->getKey()) == 0){
			return i;
		}
	}

	return -1;
}

} /* namespace alinous */
