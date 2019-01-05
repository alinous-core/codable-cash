/*
 * FeeValueFactory.cpp
 *
 *  Created on: 2019/01/06
 *      Author: iizuka
 */

#include "mempool/FeeValueFactory.h"

namespace codablecash {

FeeValueFactory::FeeValueFactory() {
}

FeeValueFactory::~FeeValueFactory() {
}

IBlockObject* FeeValueFactory::makeDataFromBinary(ByteBuffer* in) {
	// FIXME
	return nullptr;
}

} /* namespace codablecash */
