/*
 * MemoryBtreeScanner.h
 *
 *  Created on: 2020/08/13
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYBTREESCANNER_H_
#define BTREE_MEMORY_MEMORYBTREESCANNER_H_

#include "btree/IBtreeScanner.h"

namespace alinous {

class MemoryNodeCursor;
class AbstractBtreeKey;
class IBlockObject;

class MemoryBtreeScanner : public IBtreeScanner {
public:
	explicit MemoryBtreeScanner(MemoryNodeCursor* cursor);
	virtual ~MemoryBtreeScanner();

	virtual void begin();
	virtual void begin(const AbstractBtreeKey* key);
	virtual bool hasNext();

	virtual const IBlockObject* next();
	virtual const AbstractBtreeKey* nextKey();

private:
	MemoryNodeCursor* cursor;
	IBlockObject* nextObj;
	bool initialized;
	AbstractBtreeKey* key;
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYBTREESCANNER_H_ */
