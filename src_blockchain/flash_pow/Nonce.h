/*
 * Nonce.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_POW_NONCE_H_
#define FLASH_POW_NONCE_H_
#include <cstdint>

namespace codablecash {

class Nonce {
public:
	Nonce(const Nonce& inst) = default;
	Nonce(uint32_t targetDiff, uint32_t diff);
	virtual ~Nonce();

	uint32_t getDiff() const {
		return diff;
	}

	void setDiff(uint32_t diff) {
		this->diff = diff;
	}

	uint32_t getTargetDiff() const {
		return targetDiff;
	}

	void setTargetDiff(uint32_t targetDiff) {
		this->targetDiff = targetDiff;
	}

private:
	uint32_t targetDiff;
	uint32_t diff;
};

} /* namespace codablecash */

#endif /* FLASH_POW_NONCE_H_ */
