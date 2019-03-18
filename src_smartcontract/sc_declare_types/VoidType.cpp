/*
 * VoidType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/VoidType.h"

namespace alinous {

VoidType::VoidType() : AbstractType(CodeElement::TYPE_VOID) {

}

VoidType::~VoidType() {
}

} /* namespace alinous */

int alinous::VoidType::binarySize() const {
}

void alinous::VoidType::toBinary(ByteBuffer* out) {
}

void alinous::VoidType::fromBinary(ByteBuffer* in) {
}
