/*
 * LongType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "lang/sc_declare_types/LongType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString LongType::TYPE_NAME(L"long");

LongType::LongType() : AbstractPrimitiveType(CodeElement::TYPE_LONG) {
}

LongType::~LongType() {
}

int LongType::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractType::binarySize();

	return total;
}

void LongType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_LONG);
	AbstractType::toBinary(out);
}

void LongType::fromBinary(ByteBuffer* in) {
	AbstractType::fromBinary(in);
}

const UnicodeString* LongType::toString() noexcept {
	return &TYPE_NAME;
}


} /* namespace alinous */
