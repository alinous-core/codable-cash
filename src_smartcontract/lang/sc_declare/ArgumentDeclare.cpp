/*
 * ArgumentDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "lang/sc_declare/ArgumentDeclare.h"
#include "lang/sc_declare_types/AbstractType.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"


namespace alinous {

ArgumentDeclare::ArgumentDeclare() : CodeElement(CodeElement::ARGUMENT_DECLARE) {
	this->type = nullptr;
	this->name = nullptr;
	this->atype = nullptr;
}

ArgumentDeclare::~ArgumentDeclare() {
	delete this->type;
	delete this->name;
	delete this->atype;
}

void ArgumentDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void ArgumentDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

const UnicodeString* alinous::ArgumentDeclare::getName() const noexcept {
	return this->name;
}

void ArgumentDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	TypeResolver* typeResolver = actx->getTypeResolver();

	this->atype = typeResolver->resolveType(this, this->type);
	if(this->atype == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"The type '{0}' does not exists.", {this->type->toString()});
	}
	else if(this->atype->getType() == AnalyzedType::TYPE_VOID){
		actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"Cannot use void for type declare.", {});
	}

}

int alinous::ArgumentDeclare::binarySize() const {
	checkNotNull(this->type);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += this->type->binarySize();
	total += stringSize(this->name);

	return total;
}

void alinous::ArgumentDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->type);
	checkNotNull(this->name);

	out->putShort(CodeElement::ARGUMENT_DECLARE);
	this->type->toBinary(out);
	putString(out, this->name);
}

AnalyzedType* ArgumentDeclare::getAnalyzedType() const noexcept {
	return this->atype;
}

void alinous::ArgumentDeclare::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsType(element);
	checkNotNull(element);
	this->type = dynamic_cast<AbstractType*>(element);

	this->name = getString(in);
}

} /* namespace alinous */
