/*
 * MinerSignature.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_MINERSIGNATURE_H_
#define FLASH_MINERSIGNATURE_H_

namespace codablecash {

class MinerSignature {
public:
	MinerSignature(const MinerSignature& inst) = default;
	MinerSignature();
	virtual ~MinerSignature();
};

} /* namespace codablecash */

#endif /* FLASH_MINERSIGNATURE_H_ */
