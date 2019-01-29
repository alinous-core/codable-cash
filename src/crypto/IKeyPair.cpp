/*
 * IKeyPair.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "IKeyPair.h"

#include "filestore_block/exceptions.h"

namespace codablecash {

IKeyPair::~IKeyPair() {
}

IKeyPair* IKeyPair::fromBinary(ByteBuffer* in) {

	throw new BinaryFormatException(L"Wrong key pair.", __FILE__, __LINE__);
}

} /* namespace codablecash */
