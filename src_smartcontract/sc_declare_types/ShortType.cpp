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

} /* namespace alinous */

int alinous::ShortType::binarySize() const {
}

void alinous::ShortType::toBinary(ByteBuffer* out) {
}

void alinous::ShortType::fromBinary(ByteBuffer* in) {
}
