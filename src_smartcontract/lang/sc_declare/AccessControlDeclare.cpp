/*
 * AccessControlDeclare.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "lang/sc_declare/AccessControlDeclare.h"

namespace alinous {

AccessControlDeclare::AccessControlDeclare() : CodeElement(CodeElement::ACCESS_CONTROL_DECLARE) {
	this->accessCtrl = 0;
}

AccessControlDeclare::~AccessControlDeclare() {
}

void AccessControlDeclare::setCtrl(char ctrl) noexcept {
	this->accessCtrl = ctrl;
}

int AccessControlDeclare::binarySize() const {
	int total = sizeof(uint16_t);
	total += sizeof(char);

	return total;
}

void AccessControlDeclare::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::ACCESS_CONTROL_DECLARE);
	out->put(this->accessCtrl);
}

void AccessControlDeclare::fromBinary(ByteBuffer* in) {
	this->accessCtrl = in->get();
}

} /* namespace alinous */
