/*
 * BlockFileHeader.h
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKFILEHEADER_H_
#define FILESTORE_BLOCK_BLOCKFILEHEADER_H_

#include <inttypes.h>

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

	void createStore(bool del) noexcept(false);

private:
	void clearArea() noexcept;

private:
	RandomAccessFile* file;
	LongRangeList* usedArea;

};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKFILEHEADER_H_ */
