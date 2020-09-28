/*
 * FeeValueFactory.cpp
 *
 *  Created on: 2019/01/06
 *      Author: iizuka
 */

#include "mempool/IndexValueFactory.h"
#include "mempool/FposValue.h"

namespace codablecash {

IndexValueFactory::IndexValueFactory() {
}

IndexValueFactory::~IndexValueFactory() {
}

IBlockObject* IndexValueFactory::makeDataFromBinary(ByteBuffer* in) {
	// value is Fpos
	return FposValue::fromBinary(in);
}

AbstractBtreeDataFactory* IndexValueFactory::copy() const noexcept {
	return new IndexValueFactory();
}

} /* namespace codablecash */
