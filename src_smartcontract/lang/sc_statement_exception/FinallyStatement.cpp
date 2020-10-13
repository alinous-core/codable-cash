/*
 * FinallyStatement.cpp
 *
 *  Created on: 2020/04/15
 *      Author: iizuka
 */

#include "lang/sc_statement_exception/FinallyStatement.h"

#include "lang/sc_statement/StatementBlock.h"


namespace alinous {

FinallyStatement::FinallyStatement() : AbstractStatement(CodeElement::STMT_FINALLY) {
	this->block = nullptr;
}

FinallyStatement::~FinallyStatement() {
	delete this->block;
}

void FinallyStatement::preAnalyze(AnalyzeContext* actx) {
	this->block->setParent(this);
	this->block->preAnalyze(actx);
}

void FinallyStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->block->analyzeTypeRef(actx);
}

void FinallyStatement::analyze(AnalyzeContext* actx) {
	this->block->analyze(actx);
}

void FinallyStatement::init(VirtualMachine* vm) {
	this->block->init(vm);
}

void FinallyStatement::interpret(VirtualMachine* vm) {
	this->block->interpret(vm);
}

bool FinallyStatement::hasCtrlStatement() const noexcept {
	return this->block->hasCtrlStatement();
}

int FinallyStatement::binarySize() const {
	checkNotNull(this->block);

	int total = sizeof(uint16_t);

	total += this->block->binarySize();

	return total;
}

void FinallyStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->block);

	out->putShort(CodeElement::STMT_FINALLY);

	this->block->toBinary(out);
}

void FinallyStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::STMT_BLOCK);

	this->block = dynamic_cast<StatementBlock*>(element);
}

void FinallyStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

bool FinallyStatement::hasConstructor() const noexcept {
	return this->block->hasConstructor();
}

} /* namespace alinous */
