/*
 * NetworkShard.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "bc_network/NetworkShard.h"

namespace codablecash {

NetworkShard::NetworkShard(int start, int length) {
	this->begin = start;
	this->end = start + length - 1;
}

NetworkShard::~NetworkShard() {
}

} /* namespace codablecash */


