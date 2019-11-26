/*
 * StringType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/StringType.h"

#include "base/UnicodeString.h"


namespace alinous {

const UnicodeString StringType::TYPE_NAME(L"String");

StringType::StringType() : AbstractType(CodeElement::TYPE_STRING) {
}

StringType::~StringType() {
}

int StringType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void StringType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_STRING);
}

void StringType::fromBinary(ByteBuffer* in) {
}

const UnicodeString* StringType::toString() noexcept {
	return &TYPE_NAME;
}


} /* namespace alinous */
