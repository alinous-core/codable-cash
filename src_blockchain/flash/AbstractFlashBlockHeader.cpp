/*
 * AbstractFlashBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "AbstractFlashBlockHeader.h"
#include "MinerSignature.h"


namespace codablecash {

AbstractFlashBlockHeader::AbstractFlashBlockHeader() {
	this->height = 0;
	this->minerSig = nullptr;
}

AbstractFlashBlockHeader::~AbstractFlashBlockHeader() {
	delete this->minerSig;
}

} /* namespace codablecash */
