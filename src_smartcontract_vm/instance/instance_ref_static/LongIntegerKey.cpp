/*
 * LongIntegerKey.cpp
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#include "instance/instance_ref_static/LongIntegerKey.h"

namespace alinous {

LongIntegerKey::LongIntegerKey(int64_t value) {
	this->value = value;
}

LongIntegerKey::~LongIntegerKey() {
}

int LongIntegerKey::hashCode() const noexcept {
	return (int)value;
}

int LongIntegerKey::ValueCompare::operator ()(const LongIntegerKey* const _this,
												const LongIntegerKey* const object) const noexcept{

	return _this->compareTo(object);
}

int LongIntegerKey::compareTo(const LongIntegerKey* object) const noexcept {
	return value > object->value ? 1 : (value < object->value ? -1 : 0);
}

} /* namespace alinous */
