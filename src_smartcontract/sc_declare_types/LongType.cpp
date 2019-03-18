/*
 * LongType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/LongType.h"

namespace alinous {

LongType::LongType() : AbstractPrimitiveType(CodeElement::TYPE_LONG) {
}

LongType::~LongType() {
}

} /* namespace alinous */

int alinous::LongType::binarySize() const {
}

void alinous::LongType::toBinary(ByteBuffer* out) {
}

void alinous::LongType::fromBinary(ByteBuffer* in) {
}
