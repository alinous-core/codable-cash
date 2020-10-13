/*
 * ImportDeclare.cpp
 *
 *  Created on: 2019/06/17
 *      Author: iizuka
 */

#include "lang/sc_declare/ImportDeclare.h"
#include "base/UnicodeString.h"

#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "base/StackRelease.h"

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
	UnicodeString* pkg = TypeResolver::getPackageName(this->className); __STP(pkg);
	if(pkg == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_IMPORT_FORMAT, this, L"Import class format '{0}' is wrong.", {this->className});
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
	out->putShort(CodeElement::IMPORT_DECLARE);
	putString(out, this->className);
}

void ImportDeclare::fromBinary(ByteBuffer* in) {
	this->className = getString(in);
}

} /* namespace alinous */
