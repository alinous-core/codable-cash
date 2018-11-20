/*
 * BlockData.h
 *
 *  Created on: 2018/11/20
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_BLOCKDATA_H_
#define FILESTORE_BLOCK_BLOCKDATA_H_

namespace alinous {
	class ByteBuffer;
}

namespace alinous {

class BlockData {
public:
	BlockData() noexcept;
	virtual ~BlockData();

public:
	ByteBuffer* buffer;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_BLOCKDATA_H_ */
