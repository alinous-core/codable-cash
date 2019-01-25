/*
 * PoWGeneratedBlock.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef FLASH_POWGENERATEDBLOCK_H_
#define FLASH_POWGENERATEDBLOCK_H_

#include "flash/AbstractFlashBlock.h"

namespace codablecash {

class PoWGeneratedBlock: public AbstractFlashBlock {
public:
	PoWGeneratedBlock();
	virtual ~PoWGeneratedBlock();
};

} /* namespace codablecash */

#endif /* FLASH_POWGENERATEDBLOCK_H_ */
