/*
 * BlockFileBody.h
 *
 *  Created on: 2018/10/26
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKFILEBODY_H_
#define FILESTORE_BLOCK_BLOCKFILEBODY_H_

#include <inttypes.h>

namespace alinous {

class RandomAccessFile;

class BlockFileBody {
public:
	BlockFileBody(RandomAccessFile* file) noexcept;
	virtual ~BlockFileBody() noexcept;

private:
	RandomAccessFile* file;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKFILEBODY_H_ */
