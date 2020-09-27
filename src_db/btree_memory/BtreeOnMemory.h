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
class NodeHandle;
class MemoryBtreeScanner;

class BtreeOnMemory {
public:
	BtreeOnMemory(const BtreeOnMemory& inst) = delete;
	BtreeOnMemory() = delete;
	BtreeOnMemory(BtreeConfig* config, BtreeKeyFactory* factory);
	virtual ~BtreeOnMemory();

	MemoryBtreeScanner* getScanner();
	const IBlockObject* findByKey(const AbstractBtreeKey* key);

	void putData(const AbstractBtreeKey* key, IBlockObject* data);

	void setRoot(MemoryTreeNode* rootNode) noexcept;
private:
	//NodeHandle* getRootHandle() const noexcept;

private:
	BtreeKeyFactory* factory;
	BtreeConfig* config;

	MemoryTreeNode* rootNode;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_BTREEONMEMORY_H_ */
