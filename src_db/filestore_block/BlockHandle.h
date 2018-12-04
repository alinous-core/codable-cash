/*
 * BlockHandle.h
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKHANDLE_H_
#define FILESTORE_BLOCK_BLOCKHANDLE_H_

#include <inttypes.h>

namespace alinous {
class BlockFileStore;
class BlockData;
}

namespace alinous {

class BlockHandle {
public:
	BlockHandle() = delete;
	explicit BlockHandle(BlockFileStore* store) noexcept;
	virtual ~BlockHandle();

	void loadBlock(uint64_t fpos);


public:
	uint64_t fpos;

	BlockFileStore* store;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKHANDLE_H_ */
