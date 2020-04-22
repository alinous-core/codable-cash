/*
 * CastExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/CastExpression.h"
#include "sc_declare_types/AbstractType.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance_ref/PrimitiveReference.h"

#include "type_check/InternalTypeChecker.h"

#include "sc_analyze/ValidationError.h"

namespace alinous {

CastExpression::CastExpression() : AbstractExpression(CodeElement::EXP_CAST) {
	this->exp = nullptr;
	this->type = nullptr;
	this->atype = nullptr;
}

CastExpression::~CastExpression() {
	delete this->exp;
	delete this->type;
	delete this->atype;
}

void CastExpression::preAnalyze(AnalyzeContext* actx) {
	this->type->setParent(this);

	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void CastExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void CastExpression::analyze(AnalyzeContext* actx) {
	TypeResolver* resolver = actx->getTypeResolver();

	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);

	this->atype = resolver->resolveType(this, this->type);

	int result = InternalTypeChecker::analyzeCompatibility(this->atype, &at);
	if(InternalTypeChecker::INCOMPATIBLE == result){
		actx->addValidationError(ValidationError::CODE_CAST_TYPE_INCOMPATIBLE, this, L"Can not cast because of type incompatible.", {});
	}
}

void CastExpression::setType(AbstractType* type) noexcept {
	this->type = type;
}

void CastExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int CastExpression::binarySize() const {
	checkNotNull(this->exp);
	checkNotNull(this->type);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += this->type->binarySize();

	return total;
}

void CastExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	checkNotNull(this->type);

	out->putShort(CodeElement::EXP_CAST);
	this->exp->toBinary(out);
	this->type->toBinary(out);
}

void CastExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsType(element);
	this->type = dynamic_cast<AbstractType*>(element);
}

AnalyzedType CastExpression::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void CastExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* CastExpression::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);

	if(!this->atype->isArray() && (this->atype->isPrimitiveInteger() || this->atype->isBool())){
		releaser.registerInstance(inst);
		PrimitiveReference* p = dynamic_cast<PrimitiveReference*>(inst);
		return interpretPrimitive(vm, p);
	}

	return inst;
}

AbstractVmInstance* CastExpression::interpretPrimitive(VirtualMachine* vm, PrimitiveReference* p) {
	uint8_t type = this->atype->getType();

	AbstractReference* ref = nullptr;

	switch(kind){
	case CodeElement::TYPE_BOOL:
		ref = PrimitiveReference::createBoolReference(vm, 0);
		break;
	case CodeElement::TYPE_BYTE:
		ref = PrimitiveReference::createByteReference(vm, 0);
		break;
	case CodeElement::TYPE_CHAR:
		ref = PrimitiveReference::createCharReference(vm, 0);
		break;
	case CodeElement::TYPE_SHORT:
		ref = PrimitiveReference::createShortReference(vm, 0);
		break;
	case CodeElement::TYPE_INT:
		ref = PrimitiveReference::createIntReference(vm, 0);
		break;
	case CodeElement::TYPE_LONG:
	default:
		ref = PrimitiveReference::createLongReference(vm, 0);
		break;
	}

	return ref;
}

} /* namespace alinous */
