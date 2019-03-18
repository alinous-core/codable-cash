/*
 * PackageNameDeclare.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare/PackageNameDeclare.h"

#include "base/UnicodeString.h"

namespace alinous {

PackageNameDeclare::PackageNameDeclare() : CodeElement(CodeElement::PACKAGE_NAME_DECLARE) {

}

PackageNameDeclare::~PackageNameDeclare() {
	this->list.deleteElements();
}

void PackageNameDeclare::addSegment(UnicodeString* seg) {
	this->list.addElement(seg);
}


int PackageNameDeclare::binarySize() const {
}

void PackageNameDeclare::toBinary(ByteBuffer* out) {
}

void PackageNameDeclare::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
