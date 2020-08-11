/*
 * BTreeOnMemory.h
 *
 *  Created on: 2020/08/11
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_BTREEONMEMORY_H_
#define BTREE_MEMORY_BTREEONMEMORY_H_

namespace alinous {

class BtreeKeyFactory;
class AbstractBtreeDataFactory;
class BtreeConfig;
class AbstractBtreeKey;
class IBlockObject;
class MemoryTreeNode;

class BTreeOnMemory {
public:
	BTreeOnMemory(BtreeConfig* config, BtreeKeyFactory* factory, AbstractBtreeDataFactory* dfactory);
	virtual ~BTreeOnMemory();

	void insert(const AbstractBtreeKey* key, const IBlockObject* data);

private:
	BtreeKeyFactory* factory;
	AbstractBtreeDataFactory* dfactory;
	BtreeConfig* config;

	MemoryTreeNode* rootNode;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_BTREEONMEMORY_H_ */
