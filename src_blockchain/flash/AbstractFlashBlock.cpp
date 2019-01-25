/*
 * AbstractFlashBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/AbstractFlashBlock.h"
#include "MinerSignature.h"

namespace codablecash {

AbstractFlashBlock::AbstractFlashBlock(uint8_t type) {
	this->type = type;
	this->height = 0;
	this->minerSig = nullptr;
}

AbstractFlashBlock::~AbstractFlashBlock() {
	delete this->minerSig;
}



} /* namespace codablecash */
