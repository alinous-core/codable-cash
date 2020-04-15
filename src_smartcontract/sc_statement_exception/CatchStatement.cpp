/*
 * CatchStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/CatchStatement.h"

#include "sc_statement/StatementBlock.h"
#include "sc_statement/VariableDeclareStatement.h"

#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzeStackPopper.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/TypeResolver.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzedClass.h"

#include "stack/StackPopper.h"
#include "stack/VmStack.h"

#include "vm/VirtualMachine.h"

#include "base/StackRelease.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance_ref/ObjectReference.h"


namespace alinous {

CatchStatement::CatchStatement() : AbstractStatement(CodeElement::STMT_TRY_CATCH) {
	this->block = nullptr;
	this->variableDeclare = nullptr;
	this->atype = nullptr;
}

CatchStatement::~CatchStatement() {
	delete this->block;
	delete this->variableDeclare;
	delete this->atype;
}

void CatchStatement::preAnalyze(AnalyzeContext* actx) {
	this->block->setParent(this);
	this->block->preAnalyze(actx);

	this->variableDeclare->setParent(this);
	this->variableDeclare->preAnalyze(actx);
}

void CatchStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->variableDeclare->analyzeTypeRef(actx);
	this->block->analyzeTypeRef(actx);
}

void CatchStatement::analyze(AnalyzeContext* actx) {
	AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
	AnalyzeStackPopper popper(stackMgr, false);
	stackMgr->addBlockStack();

	this->variableDeclare->analyze(actx);
	this->block->analyze(actx);

	AnalyzedType at = this->variableDeclare->getType();
	uint8_t att = at.getType();
	if(att != AnalyzedType::TYPE_OBJECT || at.isArray()){
		actx->addValidationError(ValidationError::CODE_CATCH_STMT_REQUIRE_EXCEPTION, this, L"Catch statement requires exception.", {});
		return;
	}

	TypeResolver* resolver = actx->getTypeResolver();
	UnicodeString strException(L"Exception");
	AnalyzedType* exType = resolver->findClassType((const UnicodeString*)nullptr, &strException); __STP(exType);

	AnalyzedClass* ac = at.getAnalyzedClass();
	AnalyzedClass* exc = exType->getAnalyzedClass();

	if(!ac->hasBaseClass(exc)){
		actx->addValidationError(ValidationError::CODE_CATCH_STMT_REQUIRE_EXCEPTION, this, L"Catch statement requires exception.", {});
	}

	this->atype = new AnalyzedType(at);
}

void CatchStatement::init(VirtualMachine* vm) {
	if(this->block != nullptr){
		this->block->init(vm);
	}
	if(this->variableDeclare != nullptr){
		this->variableDeclare->init(vm);
	}
}

void CatchStatement::interpret(VirtualMachine* vm) {
	vm->newStack();
	StackPopper stackPopper(vm);
	StackFloatingVariableHandler releaser(vm->getGc());

	AnalyzedClass* ac = this->atype->getAnalyzedClass();
	ObjectReference* exInstRef = vm->catchException(ac);
	releaser.registerInstance(exInstRef);

	// FIXME todo
	if(exInstRef != nullptr){
		VmStack* stack = vm->topStack();

		this->variableDeclare->interpret(vm);
		AbstractReference* ref = stack->get(0);
		ref->substitute(exInstRef->getInstance(), vm);

		this->block->interpret(vm);
	}
}

bool CatchStatement::hasCtrlStatement() const noexcept {
	return true;
}

int CatchStatement::binarySize() const {
	checkNotNull(this->variableDeclare);
	checkNotNull(this->block);

	int total = sizeof(uint16_t);

	total += this->variableDeclare->binarySize();
	total += this->block->binarySize();

	return total;
}

void CatchStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->variableDeclare);
	checkNotNull(this->block);

	out->putShort(CodeElement::STMT_TRY_CATCH);

	this->variableDeclare->toBinary(out);
	this->block->toBinary(out);
}

void CatchStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::STMT_VARIABLE_DECLARE);

	this->variableDeclare = dynamic_cast<VariableDeclareStatement*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::STMT_BLOCK);

	this->block = dynamic_cast<StatementBlock*>(element);
}

void CatchStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

void CatchStatement::setVariableDeclare(VariableDeclareStatement* variableDeclare) noexcept {
	this->variableDeclare = variableDeclare;
}

} /* namespace alinous */
