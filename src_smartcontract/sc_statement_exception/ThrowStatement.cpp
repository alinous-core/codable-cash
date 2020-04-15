/*
 * ThrowStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/ThrowStatement.h"

#include "sc_expression/AbstractExpression.h"

#include "vm/VirtualMachine.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/TypeResolver.h"

#include "instance/AbstractVmInstance.h"

#include "instance_exception_class/ExceptionClassDeclare.h"
#include "instance_exception_class/VmExceptionInstance.h"


namespace alinous {

ThrowStatement::ThrowStatement() : AbstractStatement(CodeElement::STMT_THROW) {
	this->exp = nullptr;
}

ThrowStatement::~ThrowStatement() {
	delete this->exp;
}

void ThrowStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void ThrowStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void ThrowStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType atype = this->exp->getType(actx);
	uint8_t t = atype.getType();
	if(t != AnalyzedType::TYPE_OBJECT){
		actx->addValidationError(ValidationError::CODE_CATCH_STMT_REQUIRE_EXCEPTION, this, L"Catch statement requires exception.", {});
		return;
	}

	TypeResolver* resolver = actx->getTypeResolver();
	AnalyzedType* exType = resolver->findClassType(this, &ExceptionClassDeclare::NAME);

	AnalyzedClass* clazz = atype.getAnalyzedClass();
	if(!clazz->hasBaseClass(exType->getAnalyzedClass())){
		actx->addValidationError(ValidationError::CODE_CATCH_STMT_REQUIRE_EXCEPTION, this, L"Catch statement requires exception.", {});
		return;
	}

}

void ThrowStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

void ThrowStatement::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	ExecControlManager* ctrl = vm->getCtrl();

	AbstractVmInstance* inst = this->exp->interpret(vm);
	if(inst == nullptr || inst->isNull()){
		// FIXME throw nullpointerexception
		return;
	}

	IAbstractVmInstanceSubstance* sub = inst->getInstance();
	VmExceptionInstance* ex = dynamic_cast<VmExceptionInstance*>(sub);

	vm->throwException(ex, this);
}

bool ThrowStatement::hasCtrlStatement() const noexcept {
	return true;
}

int ThrowStatement::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);

	total += this->exp->binarySize();

	return total;
}

void ThrowStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_THROW);

	this->exp->toBinary(out);
}

void ThrowStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);

	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void ThrowStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
