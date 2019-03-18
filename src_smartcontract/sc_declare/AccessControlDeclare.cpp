/*
 * AccessControlDeclare.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare/AccessControlDeclare.h"

namespace alinous {

AccessControlDeclare::AccessControlDeclare() : CodeElement(CodeElement::ACCESS_CONTROL_DECLARE) {
	this->accessCtrl = 0;
}

AccessControlDeclare::~AccessControlDeclare() {
}

void AccessControlDeclare::setCtrl(char ctrl) noexcept {
	this->accessCtrl = ctrl;
}

} /* namespace alinous */

int alinous::AccessControlDeclare::binarySize() const {
}

void alinous::AccessControlDeclare::toBinary(ByteBuffer* out) {
}

void alinous::AccessControlDeclare::fromBinary(ByteBuffer* in) {
}
