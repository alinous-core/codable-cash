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

#include "stack/StackPopper.h"

#include "vm/VirtualMachine.h"


namespace alinous {

CatchStatement::CatchStatement() : AbstractStatement(CodeElement::STMT_TRY_CATCH) {
	this->block = nullptr;
	this->variableDeclare = nullptr;
}

CatchStatement::~CatchStatement() {
	delete this->block;
	delete this->variableDeclare;
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

	this->variableDeclare->interpret(vm);
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
