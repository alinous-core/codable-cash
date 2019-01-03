/*
 * AbstractAddress.cpp
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#include "bc_base/AbstractAddress.h"

namespace codablecash {

AbstractAddress::AbstractAddress(int type) {
	this->type = type;
}

AbstractAddress::~AbstractAddress() {
}

int AbstractAddress::getType() const noexcept {
	return this->type;
}

} /* namespace codablecash */
