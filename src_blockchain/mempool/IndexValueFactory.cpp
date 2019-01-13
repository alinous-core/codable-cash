/*
 * FeeValueFactory.cpp
 *
 *  Created on: 2019/01/06
 *      Author: iizuka
 */

#include "mempool/IndexValueFactory.h"

namespace codablecash {

IndexValueFactory::IndexValueFactory() {
}

IndexValueFactory::~IndexValueFactory() {
}

IBlockObject* IndexValueFactory::makeDataFromBinary(ByteBuffer* in) {
	// FIXME
	return nullptr;
}

} /* namespace codablecash */
