/*
 * DummyAddress.cpp
 *
 *  Created on: 2019/01/04
 *      Author: iizuka
 */

#include "blockchain/dummy/DummyAddress.h"


namespace codablecash {

DummyAddress::DummyAddress() : AbstractAddress(100){
}

DummyAddress::~DummyAddress() {
}

AbstractAddress* DummyAddress::clone() const noexcept {
	return nullptr;
}

bool DummyAddress::equals(const AbstractAddress* other) const noexcept{
	return false;
}

int DummyAddress::binarySize() const {
	return 0;
}

void DummyAddress::toBinary(ByteBuffer* out) const {
}

} /* namespace codablecash */


