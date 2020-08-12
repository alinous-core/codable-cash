/*
 * MemoryNodeCursor.h
 *
 *  Created on: 2020/08/12
 *      Author: iizuka
 */

#ifndef BTREE_MEMORY_MEMORYNODECURSOR_H_
#define BTREE_MEMORY_MEMORYNODECURSOR_H_

namespace alinous {

class MemoryNodeCursor {
public:
	MemoryNodeCursor(const MemoryNodeCursor& inst) = delete;
	MemoryNodeCursor();
	virtual ~MemoryNodeCursor();
};

} /* namespace alinous */

#endif /* BTREE_MEMORY_MEMORYNODECURSOR_H_ */
