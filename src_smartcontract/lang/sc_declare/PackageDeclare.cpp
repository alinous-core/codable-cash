/*
 * PackageDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "lang/sc_declare/PackageDeclare.h"
#include "lang/sc_declare/PackageNameDeclare.h"

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

const UnicodeString* PackageDeclare::getPackageName() noexcept {
	return this->name->getName();
}

int PackageDeclare::binarySize() const {
	int total = sizeof(uint16_t);

	checkNotNull(this->name);
	total += this->name->binarySize();

	return total;
}

void PackageDeclare::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::PACKAGE_DECLARE);

	this->name->toBinary(out);
}

void PackageDeclare::fromBinary(ByteBuffer* in) {
	CodeElement* nm = CodeElement::createFromBinary(in);
	checkKind(nm, CodeElement::PACKAGE_NAME_DECLARE);

	this->name = dynamic_cast<PackageNameDeclare*>(nm);
}


} /* namespace alinous */
