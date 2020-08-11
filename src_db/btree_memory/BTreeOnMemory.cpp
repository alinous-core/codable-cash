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

namespace alinous {

BTreeOnMemory::BTreeOnMemory(BtreeConfig* config, BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory) {
	this->config = config;
	this->factory = factory;
	this->dfactory = dfactory;

	InfinityKey* infinityKey = new InfinityKey();
	this->rootNode = new MemoryTreeNode(true, config->nodeNumber, infinityKey, true);
}

BTreeOnMemory::~BTreeOnMemory() {
	delete this->rootNode;

	delete this->config;
	delete this->factory;
	delete this->dfactory;
}

void BTreeOnMemory::insert(const AbstractBtreeKey* key,	const IBlockObject* data) {
}

} /* namespace alinous */
