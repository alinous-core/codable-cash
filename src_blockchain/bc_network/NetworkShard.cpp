/*
 * NetworkShard.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "bc_network/NetworkShard.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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


} /* namespace codablecash */

