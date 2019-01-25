/*
 * BlockFileHeader.h
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKFILEHEADER_H_
#define FILESTORE_BLOCK_BLOCKFILEHEADER_H_

#include <cstdint>

namespace alinous {
class RandomAccessFile;
class LongRangeList;
}

namespace alinous {
class BlockFileHeader {
public:
	BlockFileHeader(const BlockFileHeader& base) = delete;
	explicit BlockFileHeader(RandomAccessFile* file) noexcept;
	virtual ~BlockFileHeader() noexcept;

	void createStore(bool del, uint64_t defaultSize, uint64_t blockSize) noexcept(false);

	//void sync2File() noexcept(false);
	void sync(bool fileSync=true) noexcept(false);
	void sync2File() noexcept(false);
	void loadFromFile() noexcept(false);

	uint64_t alloc();
	void remove(uint64_t fpos);

	inline uint64_t getBlockSize() noexcept {
		return this->blockSize;
	}
private:
	void clearArea() noexcept;



private:
	RandomAccessFile* file;
	LongRangeList* usedArea;
	uint64_t blockSize;

};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKFILEHEADER_H_ */
