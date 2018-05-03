/*
 * CoderResult.cpp
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#include "debug/debugMacros.h"
#include "charsets/CoderResult.h"

namespace alinous {

const CoderResult CoderResult::__UNDERFLOW{CoderResult::TYPE_UNDERFLOW, 0};
const CoderResult CoderResult::__OVERFLOW{CoderResult::TYPE_OVERFLOW, 0};

CoderResult::CoderResult(int type, int length) noexcept {
	this->type = type;
	this->length = length;
}

CoderResult::~CoderResult() {
}

} /* namespace alinous */
