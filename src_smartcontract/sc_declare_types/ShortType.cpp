/*
 * ShortType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/ShortType.h"

namespace alinous {

ShortType::ShortType() : AbstractPrimitiveType(CodeElement::TYPE_SHORT) {
}

ShortType::~ShortType() {
}

int ShortType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void ShortType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_SHORT);
}

void ShortType::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
