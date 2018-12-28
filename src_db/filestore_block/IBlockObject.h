/*
 * IBlockObject.h
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#ifndef FILESTORE_BLOCK_IBLOCKOBJECT_H_
#define FILESTORE_BLOCK_IBLOCKOBJECT_H_

namespace alinous {

class ByteBuffer;

class IBlockObject {
public:
	IBlockObject(){}
	virtual ~IBlockObject(){};

	virtual int binarySize() const = 0;
	virtual void toBinary(ByteBuffer* out) const = 0;
};

} /* namespace alinous */

#endif /* FILESTORE_BLOCK_IBLOCKOBJECT_H_ */
