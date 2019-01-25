/*
 * BlockData.h
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKDATA_H_
#define FILESTORE_BLOCK_BLOCKDATA_H_

#include <cstdint>

namespace alinous {
	class ByteBuffer;
}

namespace alinous {

class BlockData {
public:
	static constexpr int HEADER_SIZE{sizeof(uint64_t)*2 + sizeof(uint16_t)};

	BlockData(const BlockData& obj) = delete;
	BlockData(uint16_t blockSize, uint64_t fpos, uint16_t used, uint64_t nextfpos, const char* data) noexcept;
	virtual ~BlockData();

	inline uint16_t headerSize() noexcept {
		return sizeof(uint16_t) + sizeof(uint64_t);
	}

	inline uint16_t dataSize() noexcept {
		return this->blockSize - headerSize();
	}

	static BlockData* createNewBlock(uint64_t blockSize, uint64_t fpos, uint16_t used, uint64_t nextfpos);
	static BlockData* fromBinary(uint64_t blockSize, const char* bin, int length);

	void updateData(const char* ptr, int length) noexcept;
	void updateNextFpos(uint64_t nextfpos) noexcept {
		this->nextfpos = nextfpos;
	}

	uint64_t getCurrentfPos() const noexcept {
		return currentfPos;
	}
	const char* getData() const {
		return data;
	}
	uint64_t getNextfpos() const noexcept {
		return nextfpos;
	}
	uint16_t getUsed() const noexcept {
		return used;
	}

private:
	uint16_t blockSize;
	uint64_t currentfPos;

	// header
	uint64_t nextfpos;
	uint16_t used;


	// body
	char* data;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKDATA_H_ */
