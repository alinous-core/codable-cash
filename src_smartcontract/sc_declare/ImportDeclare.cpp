/*
 * ImportDeclare.cpp
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#include "sc_declare/ImportDeclare.h"
#include "base/UnicodeString.h"

namespace alinous {

ImportDeclare::ImportDeclare() : CodeElement(CodeElement::IMPORT_DECLARE) {
	this->className = nullptr;
}

ImportDeclare::~ImportDeclare() {
	delete this->className;
}


void ImportDeclare::appendStr(const char* cstr) noexcept {
	if(this->className == nullptr){
		this->className = new UnicodeString(L"");
	}

	UnicodeString str(cstr);
	this->className->append(&str);
}

int ImportDeclare::binarySize() const {
	int total = sizeof(uint16_t);

	total += stringSize(this->className);

	return total;
}

void ImportDeclare::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::IMPORTS_DECLARE);
	putString(out, this->className);
}

void ImportDeclare::fromBinary(ByteBuffer* in) {
	this->className = getString(in);
}

} /* namespace alinous */
