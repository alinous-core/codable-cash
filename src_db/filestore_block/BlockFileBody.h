/*
 * BlockFileBody.h
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKFILEBODY_H_
#define FILESTORE_BLOCK_BLOCKFILEBODY_H_

#include <cstdint>

namespace alinous {

class RandomAccessFile;
class BlockData;

class BlockFileBody {
public:
	BlockFileBody(const BlockFileBody& base) = delete;
	explicit BlockFileBody(RandomAccessFile* file, uint64_t blockSize) noexcept;
	virtual ~BlockFileBody() noexcept;

	void createStore(bool del, uint64_t blockSize) noexcept(false);

	uint64_t alloc(uint64_t fpos, uint64_t used, uint64_t nextfpos);
	void writeBlock(BlockData* data);
	BlockData* loadBlock(uint64_t fpos);

	void sync(bool fileSync);

	inline uint64_t getBlockSize(){
		return this->blockSize;
	}

private:
	RandomAccessFile* file;
	uint64_t blockSize;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKFILEBODY_H_ */
