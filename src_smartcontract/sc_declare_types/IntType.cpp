/*
 * IntType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/IntType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString IntType::TYPE_NAME(L"String");

IntType::IntType()  : AbstractPrimitiveType(CodeElement::TYPE_INT) {

}

IntType::~IntType() {
}


int IntType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void IntType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_INT);
}

void IntType::fromBinary(ByteBuffer* in) {
}

const UnicodeString* IntType::toString() noexcept {
	return &TYPE_NAME;
}

} /* namespace alinous */
