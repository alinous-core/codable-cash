/*
 * ImportDeclare.cpp
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#include "sc_declare/ImportDeclare.h"
#include "base/UnicodeString.h"

#include "sc_analyze/TypeResolver.h"

namespace alinous {

ImportDeclare::ImportDeclare() : CodeElement(CodeElement::IMPORT_DECLARE) {
	this->className = nullptr;
	this->namePart = nullptr;
}

ImportDeclare::~ImportDeclare() {
	delete this->className;
	delete this->namePart;
}


void ImportDeclare::appendStr(const char* cstr) noexcept {
	if(this->className == nullptr){
		this->className = new UnicodeString(L"");
	}

	UnicodeString str(cstr);
	this->className->append(&str);
}

bool ImportDeclare::hasClassName(const UnicodeString* name) noexcept {
	if(this->namePart == nullptr){
		this->namePart = TypeResolver::getClassName(this->className);
	}

	return this->namePart->equals(name);
}

void ImportDeclare::preAnalyze(AnalyzeContext* actx) {
	UnicodeString* pkg = TypeResolver::getPackageName(this->className);
	if(pkg == nullptr){
		// FIXME add error

	}
}

UnicodeString* ImportDeclare::getPackageName() noexcept {
	return TypeResolver::getPackageName(this->className);
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
