/*
 * Nonce.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "Nonce.h"

namespace codablecash {

Nonce::Nonce(uint32_t targetDiff, uint32_t diff) {
	this->targetDiff = targetDiff;
	this->diff = diff;
}

Nonce::~Nonce() {
}

} /* namespace codablecash */
