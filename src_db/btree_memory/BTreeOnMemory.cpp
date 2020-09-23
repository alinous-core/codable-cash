/*
 * BTreeOnMemory.cpp
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#include "btree_memory/BTreeOnMemory.h"

#include "btreekey/BtreeKeyFactory.h"
#include "btreekey/InfinityKey.h"

#include "btree/AbstractBtreeDataFactory.h"
#include "btree/BtreeConfig.h"

#include "btree_memory/MemoryTreeNode.h"
#include "btree_memory/MemoryNodeHandle.h"
#include "btree_memory/MemoryNodeCursor.h"
#include "btree_memory/MemoryBtreeScanner.h"

namespace alinous {

BTreeOnMemory::BTreeOnMemory(BtreeConfig* config, BtreeKeyFactory* factory) {
	this->config = config;
	this->factory = factory;

	InfinityKey* infinityKey = new InfinityKey();
	this->rootNode = new MemoryTreeNode(true, config->nodeNumber, infinityKey, true);
}

BTreeOnMemory::~BTreeOnMemory() {
	delete this->rootNode;

	delete this->config;
	delete this->factory;
}

MemoryBtreeScanner* BTreeOnMemory::getScanner() {
	MemoryNodeHandle* rootNode = new MemoryNodeHandle(this->rootNode);
	MemoryNodeCursor* cursor = new MemoryNodeCursor(rootNode, this->config->nodeNumber, this);

	return new MemoryBtreeScanner(cursor);
}

void BTreeOnMemory::putData(const AbstractBtreeKey* key,	IBlockObject* data) {
	MemoryNodeHandle* rootNode = new MemoryNodeHandle(this->rootNode);

	MemoryNodeCursor cursor(rootNode, this->config->nodeNumber, this);
	cursor.insert(key, data);

}

void BTreeOnMemory::setRoot(MemoryTreeNode* rootNode) noexcept {
	this->rootNode = rootNode;
}

} /* namespace alinous */
