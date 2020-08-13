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
	MemoryBtreeScanner(MemoryNodeCursor* cursor);
	virtual ~MemoryBtreeScanner();

private:
	MemoryNodeCursor* cursor;
	IBlockObject* nextObj;
	bool initialized;
	AbstractBtreeKey* key;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYBTREESCANNER_H_ */
