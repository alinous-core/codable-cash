/*
 * BoolType.cpp
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#include "sc_declare_types/BoolType.h"

namespace alinous {

BoolType::BoolType() : AbstractPrimitiveType(CodeElement::TYPE_BOOL) {

}

BoolType::~BoolType() {

}

int BoolType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void BoolType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_CHAR);
}

void BoolType::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
