/*
 * StringType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/StringType.h"

namespace alinous {

StringType::StringType() : AbstractType(CodeElement::TYPE_STRING) {
}

StringType::~StringType() {
}

} /* namespace alinous */

int alinous::StringType::binarySize() const {
}

void alinous::StringType::toBinary(ByteBuffer* out) {
}

void alinous::StringType::fromBinary(ByteBuffer* in) {
}
