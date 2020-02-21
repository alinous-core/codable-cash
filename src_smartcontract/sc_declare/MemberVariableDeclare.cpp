/*
 * MemberVariableDeclare.cpp
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#include "sc_declare/MemberVariableDeclare.h"
#include "sc_declare/AccessControlDeclare.h"
#include "sc_declare_types/AbstractType.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/ValidationError.h"

#include "sc_expression/AbstractExpression.h"

#include "sc/exceptions.h"

#include "vm/VirtualMachine.h"


namespace alinous {

MemberVariableDeclare::MemberVariableDeclare() : CodeElement(CodeElement::MEMBER_VARIABLE_DECLARE) {
	this->ctrl = nullptr;
	this->type = nullptr;
	this->_static = false;
	this->name = nullptr;
	this->exp = nullptr;
	this->atype = nullptr;
}

MemberVariableDeclare::~MemberVariableDeclare() {
	delete this->ctrl;
	delete this->type;
	delete this->name;
	delete this->exp;
	delete this->atype;
}

void MemberVariableDeclare::preAnalyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->setParent(this);
		this->exp->preAnalyze(actx);
	}
}

void MemberVariableDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyzeTypeRef(actx);
	}

	TypeResolver* typeResolver = actx->getTypeResolver();

	this->atype = typeResolver->resolveType(this, this->type);
	if(this->atype == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"The type '{0}' does not exists.", {this->type->toString()});
	}
	else if(this->atype->getType() == AnalyzedType::TYPE_VOID){
		actx->addValidationError(ValidationError::CODE_WRONG_TYPE_NAME, this, L"Cannot use void for type declare.", {});
	}
}

void MemberVariableDeclare::analyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyze(actx);
	}
}

void MemberVariableDeclare::init(VirtualMachine* vm) {
	if(!this->_static){
		return;
	}

	// FIXME handle a static member
}


void MemberVariableDeclare::setAccessControl(AccessControlDeclare* ctrl) noexcept {
	this->ctrl = ctrl;
}

void MemberVariableDeclare::setType(AbstractType* type) noexcept {
	this->type = type;
}

void MemberVariableDeclare::setStatic(bool s) noexcept {
	this->_static = s;
}

void MemberVariableDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

const UnicodeString* MemberVariableDeclare::getName() noexcept {
	return this->name;
}

AbstractType* MemberVariableDeclare::getType() noexcept {
	return this->type;
}

void MemberVariableDeclare::setExp(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int MemberVariableDeclare::binarySize() const {
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	bool isnull = (this->exp == nullptr);
	total += sizeof(uint8_t);
	if(!isnull){
		total += this->exp->binarySize();
	}

	total += sizeof(uint8_t);
	total += this->ctrl->binarySize();
	total += this->type->binarySize();
	total += stringSize(this->name);

	return total;
}

void MemberVariableDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->ctrl);
	checkNotNull(this->type);
	checkNotNull(this->name);

	out->putShort(CodeElement::MEMBER_VARIABLE_DECLARE);

	bool isnull = (this->exp == nullptr);
	out->put(isnull ? (char)1 : (char)0);
	if(!isnull){
		this->exp->toBinary(out);
	}

	out->put(this->_static ? (char)1 : (char)0);
	this->ctrl->toBinary(out);
	this->type->toBinary(out);
	putString(out, this->name);
}

void MemberVariableDeclare::fromBinary(ByteBuffer* in) {

	uint8_t bl = in->get();
	if(bl == 0){
		CodeElement* element = createFromBinary(in);
		checkIsExp(element);
		this->exp = dynamic_cast<AbstractExpression*>(element);
	}

	bl = in->get();
	this->_static = (bl == 1);

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::ACCESS_CONTROL_DECLARE);
	this->ctrl = dynamic_cast<AccessControlDeclare*>(element);

	element = createFromBinary(in);
	checkIsType(element);

	this->type = dynamic_cast<AbstractType*>(element);

	this->name = getString(in);
}

} /* namespace alinous */
