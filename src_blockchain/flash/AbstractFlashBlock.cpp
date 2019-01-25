/*
 * AbstractFlashBlock.cpp
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#include "flash/AbstractFlashBlock.h"

#include "bc_base/AbstractTransaction.h"
#include "MinerSignature.h"

namespace codablecash {

AbstractFlashBlock::AbstractFlashBlock(uint8_t type) {
	this->type = type;
	this->header = nullptr;
}

AbstractFlashBlock::~AbstractFlashBlock() {
	this->list.deleteElements();
}



} /* namespace codablecash */
