/*
 * CharType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/CharType.h"

namespace alinous {

CharType::CharType() : AbstractPrimitiveType(CodeElement::TYPE_CHAR) {
}

CharType::~CharType() {
}

} /* namespace alinous */

int alinous::CharType::binarySize() const {
}

void alinous::CharType::toBinary(ByteBuffer* out) {
}

void alinous::CharType::fromBinary(ByteBuffer* in) {
}
