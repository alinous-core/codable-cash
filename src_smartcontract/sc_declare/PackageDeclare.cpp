/*
 * PackageDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/PackageDeclare.h"
#include "sc_declare/PackageNameDeclare.h"

namespace alinous {

PackageDeclare::PackageDeclare() : CodeElement(CodeElement::PACKAGE_DECLARE){
	this->name = nullptr;
}

PackageDeclare::~PackageDeclare() {
	if(this->name){
		delete this->name;
	}
}

void PackageDeclare::setName(PackageNameDeclare* name) {
	this->name = name;
}

int PackageDeclare::binarySize() const {
}

void PackageDeclare::toBinary(ByteBuffer* out) {
}

void PackageDeclare::fromBinary(ByteBuffer* in) {
}


} /* namespace alinous */
