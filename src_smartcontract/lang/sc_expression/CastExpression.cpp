/*
 * CastExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression/CastExpression.h"
#include "lang/sc_declare_types/AbstractType.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/TypeResolver.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "vm/type_check/InternalTypeChecker.h"

#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzedClass.h"

#include "instance/instance_exception/ExceptionInterrupt.h"
#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"


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

	if(this->atype == nullptr){
		this->atype = new AnalyzedType();
		actx->addValidationError(ValidationError::CODE_CAST_TYPE_NOT_EXIST, this, L"Can not cast because type does not exist.", {});
		return;
	}


	if(this->atype->isBool()){
		if(!at.isPrimitiveInteger() && !at.isBool()){
			actx->addValidationError(ValidationError::CODE_CAST_TYPE_INCOMPATIBLE, this, L"Can not cast because of type incompatible.", {});
		}
	}
	else{
		int result = InternalTypeChecker::analyzeCompatibility(this->atype, &at);
		if(InternalTypeChecker::INCOMPATIBLE == result){
			result = InternalTypeChecker::analyzeCompatibility(&at, this->atype);
			if(InternalTypeChecker::INCOMPATIBLE == result){
				actx->addValidationError(ValidationError::CODE_CAST_TYPE_INCOMPATIBLE, this, L"Can not cast because of type incompatible.", {});
			}
		}
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

	if(inst == nullptr || inst->isNull()){
		return nullptr;
	}
	if(!this->atype->isArray() && (this->atype->isPrimitiveInteger() || this->atype->isBool())){
		releaser.registerInstance(inst);
		PrimitiveReference* p = dynamic_cast<PrimitiveReference*>(inst);
		return interpretPrimitive(vm, p);
	}
	else if(this->atype->isArray()){
		return checkArrayType(vm, inst, &releaser);
	}

	IAbstractVmInstanceSubstance* sub = inst->getInstance();
	AnalyzedType at = sub->getRuntimeType();
	AnalyzedClass* clazz =  at.getAnalyzedClass();

	AnalyzedClass* expClazz = this->atype->getAnalyzedClass();

	if(!expClazz->hasBaseClass(clazz)){
		releaser.registerInstance(inst);

		TypeCastExceptionClassDeclare::throwException(vm, this);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return inst;
}

AbstractVmInstance* CastExpression::checkArrayType(VirtualMachine* vm, AbstractVmInstance* inst, StackFloatingVariableHandler* releaser) {
	AnalyzedType at = inst->getInstance()->getRuntimeType();
	if(!this->atype->equals(&at)){
		releaser->registerInstance(inst);

		TypeCastExceptionClassDeclare::throwException(vm, this);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return inst;
}

AbstractVmInstance* CastExpression::interpretPrimitive(VirtualMachine* vm, PrimitiveReference* p) {
	uint8_t type = this->atype->getType();

	AbstractReference* ref = nullptr;

	int64_t value = p->getLongValue();

	switch(type){
	case AnalyzedType::TYPE_BOOL:
		ref = PrimitiveReference::createBoolReference(vm, (int32_t)value);
		break;
	case AnalyzedType::TYPE_BYTE:
		ref = PrimitiveReference::createByteReference(vm, (int8_t)value);
		break;
	case AnalyzedType::TYPE_CHAR:
		ref = PrimitiveReference::createCharReference(vm, (int16_t)value);
		break;
	case AnalyzedType::TYPE_SHORT:
		ref = PrimitiveReference::createShortReference(vm, (int16_t)value);
		break;
	case AnalyzedType::TYPE_INT:
		ref = PrimitiveReference::createIntReference(vm, (int32_t)value);
		break;
	case AnalyzedType::TYPE_LONG:
	default:
		ref = PrimitiveReference::createLongReference(vm, value);
		break;
	}

	return ref;
}

} /* namespace alinous */
