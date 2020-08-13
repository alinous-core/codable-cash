/*
 * MemoryBtreeScanner.h
 *
 *  Created on: 2020/08/13
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYBTREESCANNER_H_
#define BTREE_MEMORY_MEMORYBTREESCANNER_H_

namespace alinous {

class MemoryNodeCursor;
class AbstractBtreeKey;
class IBlockObject;

class MemoryBtreeScanner {
public:
	explicit MemoryBtreeScanner(MemoryNodeCursor* cursor);
	virtual ~MemoryBtreeScanner();

	void begin();
	void begin(const AbstractBtreeKey* key);
	bool hasNext();
	const IBlockObject* next();

private:
	MemoryNodeCursor* cursor;
	IBlockObject* nextObj;
	bool initialized;
	AbstractBtreeKey* key;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYBTREESCANNER_H_ */
