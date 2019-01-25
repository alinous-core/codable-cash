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

class MinerSignature;

class AbstractFlashBlock {
public:
	static const constexpr uint8_t BLK_TICKET{0x01};
	static const constexpr uint8_t BLK_POW{0x02};

	AbstractFlashBlock(uint8_t type);
	virtual ~AbstractFlashBlock();


protected:
	uint8_t type;
	uint64_t height;
	MinerSignature* minerSig;
};

} /* namespace codablecash */

#endif /* FLASH_ABSTRACTFLASHBLOCK_H_ */
