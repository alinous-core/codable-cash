/*
 * CoderResult.cpp
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#include "debug/debugMacros.h"
#include "charsets/CoderResult.h"

namespace alinous {

const CoderResult CoderResult::UNDERFLOW{CoderResult::TYPE_UNDERFLOW, 0};
const CoderResult CoderResult::OVERFLOW{CoderResult::TYPE_OVERFLOW, 0};

CoderResult::CoderResult(int type, int length) noexcept : type(type), length(length) {
}

CoderResult::~CoderResult() {
}

} /* namespace alinous */
