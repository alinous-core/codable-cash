/*
 * LongKey.cpp
 *
 *  Created on: 2018/12/23
 *      Author: iizuka
 */

#include "btreekey/ULongKey.h"


namespace alinous {

ULongKey::ULongKey(uint64_t value) {
	this->value = value;
}

ULongKey::~ULongKey() {
}

} /* namespace alinous */
