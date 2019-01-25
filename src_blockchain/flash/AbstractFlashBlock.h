/*
 * AbstractFlashBlock.h
 *
 *  Created on: 2019/01/23
 *      Author: iizuka
 */

#ifndef FLASH_ABSTRACTFLASHBLOCK_H_
#define FLASH_ABSTRACTFLASHBLOCK_H_
#include <cstdint>

namespace codablecash {

class AbstractFlashBlock {
public:
	virtual ~AbstractFlashBlock();
	AbstractFlashBlock();

protected:
	uint64_t height;
};

} /* namespace codablecash */

#endif /* FLASH_ABSTRACTFLASHBLOCK_H_ */
