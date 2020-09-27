/*
 * NetworkShard.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "base_io/ByteBuffer.h"
#include "bc_network/NetworkShard.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using alinous::ByteBuffer;

namespace codablecash {

NetworkShard::NetworkShard() {
	this->begin = 0;
	this->end = 0;
}

NetworkShard::NetworkShard(int start, int length) {
	this->begin = start;
	this->end = start + length - 1;
}

NetworkShard::~NetworkShard() {
}

char NetworkShard::getRandomHash() const noexcept {
	srand((unsigned)time(NULL));

	int value = rand();
	value = value % size();

	return this->begin + value;
}

int NetworkShard::size() const noexcept {
	return this->end - this->begin + 1;
}

NetworkShard* NetworkShard::clone() const noexcept {
	NetworkShard* newShard =  new NetworkShard();
	newShard->begin = this->begin;
	newShard->end = this->end;

	return newShard;
}


int NetworkShard::binarySize() const {
	return sizeof(this->begin) + sizeof(this->end);
}

void NetworkShard::toBinary(ByteBuffer* out) const {
	out->putInt(this->begin);
	out->putInt(this->end);
}

NetworkShard* NetworkShard::fromBinary(ByteBuffer* in) {
	int32_t begin = in->getInt();
	int32_t end = in->getInt();

	return new NetworkShard(begin, end - begin + 1);
}

IBlockObject* NetworkShard::copyData() const noexcept {
	return new NetworkShard(*this);
}

} /* namespace codablecash */
