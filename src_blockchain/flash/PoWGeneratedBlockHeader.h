/*
 * PoWGeneratedBlockHeader.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_POWGENERATEDBLOCKHEADER_H_
#define FLASH_POWGENERATEDBLOCKHEADER_H_

#include "AbstractFlashBlockHeader.h"

namespace codablecash {

class Nonce;

class PoWGeneratedBlockHeader : public AbstractFlashBlockHeader {
public:
	PoWGeneratedBlockHeader();
	virtual ~PoWGeneratedBlockHeader();

private:
	Nonce* nonce;
};

} /* namespace codablecash */

#endif /* FLASH_POWGENERATEDBLOCKHEADER_H_ */
