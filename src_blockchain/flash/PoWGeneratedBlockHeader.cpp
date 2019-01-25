/*
 * PoWGeneratedBlockHeader.cpp
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#include "PoWGeneratedBlockHeader.h"

#include "flash_pow/Nonce.h"

namespace codablecash {

PoWGeneratedBlockHeader::PoWGeneratedBlockHeader() {
	this->nonce = nullptr;

}

PoWGeneratedBlockHeader::~PoWGeneratedBlockHeader() {
	delete this->nonce;
}

} /* namespace codablecash */
