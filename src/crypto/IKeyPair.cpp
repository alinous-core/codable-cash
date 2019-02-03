/*
 * IKeyPair.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "IKeyPair.h"

#include "filestore_block/exceptions.h"
#include "base_io/ByteBuffer.h"
#include "SchnorrKeyPair.h"

namespace codablecash {

IKeyPair::~IKeyPair() {
}

IKeyPair* IKeyPair::createFromBinary(ByteBuffer* in) {
	int32_t type = in->get();

	IKeyPair* pair = nullptr;
	switch (type) {
		case IKeyPair::PAIR_SCHNORR:
			pair = new SchnorrKeyPair();
			break;
		default:
			throw new BinaryFormatException(L"Wrong key pair.", __FILE__, __LINE__);
	}

	pair->fromBinary(in);

	return pair;
}

} /* namespace codablecash */
