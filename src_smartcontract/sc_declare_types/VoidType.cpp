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

int VoidType::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void VoidType::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::TYPE_VOID);
}

void VoidType::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
