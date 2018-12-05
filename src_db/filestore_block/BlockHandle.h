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
class ByteBuffer;
}

namespace alinous {

class BlockHandle {
	friend class BlockFileStore;
public:
	BlockHandle() = delete;
	explicit BlockHandle(BlockFileStore* store) noexcept;
	virtual ~BlockHandle();

	void loadBlock(uint64_t fpos);


	int size() noexcept;

private:
	void initOnAlloc(uint64_t fpos, int size) noexcept;

private:
	uint64_t fpos;
	BlockFileStore* store;
	ByteBuffer* buffer;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKHANDLE_H_ */
