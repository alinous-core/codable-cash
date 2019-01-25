/*
 * AbstractFlashBlockHeader.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_ABSTRACTFLASHBLOCKHEADER_H_
#define FLASH_ABSTRACTFLASHBLOCKHEADER_H_

#include <cstdint>

namespace codablecash {

class MinerSignature;

class AbstractFlashBlockHeader {
public:
	AbstractFlashBlockHeader();
	virtual ~AbstractFlashBlockHeader();

protected:
	uint64_t height;
	MinerSignature* minerSig;
};

} /* namespace codablecash */

#endif /* FLASH_ABSTRACTFLASHBLOCKHEADER_H_ */
