/*
 * ClassExtends.cpp
 *
 *  Created on: 2019/06/19
 *      Author: iizuka
 */

#include "lang/sc_declare/ClassExtends.h"
#include "lang/sc_declare/ClassName.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"

#include "base/UnicodeString.h"


namespace alinous {

ClassExtends::ClassExtends() : CodeElement(CodeElement::CLASS_EXTENDS) {
	this->className = nullptr;
	this->atype = nullptr;
}

ClassExtends::~ClassExtends() {
	delete this->className;
	delete this->atype;
}

void ClassExtends::preAnalyze(AnalyzeContext* actx) {
}


void ClassExtends::analyzeTypeRef(AnalyzeContext* actx) {
	const UnicodeString* name = this->className->getName();
	TypeResolver* res = actx->getTypeResolver();

	this->atype = res->findClassType(this, name);
	if(this->atype == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_CLASS_NAME, this, L"The class '{0}' does not exists.", {name});
	}
}


void ClassExtends::setClassName(ClassName* className) noexcept {
	this->className = className;
}

void ClassExtends::setClassName(const UnicodeString* className) noexcept {
	this->className = new ClassName();
	this->className->addStr(className);
}

AnalyzedType* ClassExtends::getAnalyzedType() const noexcept {
	return this->atype;
}


int ClassExtends::binarySize() const {
	checkNotNull(this->className);

	int total = sizeof(uint16_t);
	total += this->className->binarySize();

	return total;
}

void ClassExtends::toBinary(ByteBuffer* out) {
	checkNotNull(this->className);

	out->putShort(CodeElement::CLASS_EXTENDS);
	this->className->toBinary(out);
}

void ClassExtends::fromBinary(ByteBuffer* in) {
	CodeElement* element = CodeElement::createFromBinary(in);
	CodeElement::checkKind(element, CodeElement::CLASS_NAME);

	this->className = dynamic_cast<ClassName*>(element);
}

} /* namespace alinous */
