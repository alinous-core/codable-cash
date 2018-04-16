/*
 * CoderResult.cpp
 *
 *  Created on: 2018/04/16
 *      Author: iizuka
 */

#include <charsets/CoderResult.h>

namespace alinous {

const CoderResult CoderResult::UNDERFLOW(CoderResult::CR_UNDERFLOW, 0);
const CoderResult CoderResult::OVERFLOW(CoderResult::CR_OVERFLOW, 0);

CoderResult::CoderResult(int type, int length) noexcept : type(type), length(length) {
}

CoderResult::~CoderResult() {
}

} /* namespace alinous */
