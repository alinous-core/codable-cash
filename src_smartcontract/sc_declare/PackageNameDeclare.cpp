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
	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* str = this->list.get(i);
		total += sizeof(uint32_t);
		total += str->length() * sizeof(uint16_t);
	}

	return total;
}

void PackageNameDeclare::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::PACKAGE_NAME_DECLARE);

	uint8_t maxLoop = this->list.size();
	out->put(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* str = this->list.get(i);
		putString(out, str);
	}
}

void PackageNameDeclare::fromBinary(ByteBuffer* in) {
	uint8_t maxLoop = in->get();
	for(int i = 0; i != maxLoop; ++i){
		UnicodeString* str = getString(in);
		this->list.addElement(str);
	}
}

} /* namespace alinous */
