/*
 * BoolType.cpp
 *
 *  Created on: 2019/06/11
 *      Author: iizuka
 */

#include "lang/sc_declare_types/BoolType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString BoolType::TYPE_NAME(L"boolean");

BoolType::BoolType() : AbstractPrimitiveType(CodeElement::TYPE_BOOL) {

}

BoolType::~BoolType() {

}

int BoolType::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractType::binarySize();

	return total;
}

void BoolType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_BOOL);
	AbstractType::toBinary(out);
}

void BoolType::fromBinary(ByteBuffer* in) {
	AbstractType::fromBinary(in);
}

const UnicodeString* BoolType::toString() noexcept {
	return &TYPE_NAME;
}

void BoolType::setType(short kind) noexcept {
	this->kind = kind;
}

} /* namespace alinous */
