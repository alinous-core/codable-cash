/*
 * BlockData.h
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKDATA_H_
#define FILESTORE_BLOCK_BLOCKDATA_H_

#include <inttypes.h>

namespace alinous {
	class ByteBuffer;
}

namespace alinous {

class BlockData {
public:
	BlockData(uint16_t blockSize, uint64_t currentPos) noexcept;
	virtual ~BlockData();

	inline uint16_t headerSize() noexcept {
		return sizeof(uint16_t) + sizeof(uint64_t);
	}

	inline uint16_t dataSize() noexcept {
		return this->blockSize - headerSize();
	}



private:
	uint16_t blockSize;
	uint64_t currentPos;

	// header
	uint16_t used;
	uint64_t nextPos;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKDATA_H_ */
