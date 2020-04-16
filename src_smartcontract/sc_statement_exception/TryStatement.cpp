/*
 * TryStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/TryStatement.h"

#include "sc_statement/StatementBlock.h"
#include "sc_statement_exception/CatchStatement.h"
#include "sc_statement_exception/FinallyStatement.h"


namespace alinous {

TryStatement::TryStatement() : AbstractStatement(CodeElement::STMT_TRY) {
	this->block = nullptr;
	this->finallyStmt = nullptr;
}

TryStatement::~TryStatement() {
	delete this->block;
	this->catchStmts.deleteElements();
	delete this->finallyStmt;
}

void TryStatement::preAnalyze(AnalyzeContext* actx) {
	this->block->setParent(this);
	this->block->preAnalyze(actx);

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		catchStmt->setParent(this);
		catchStmt->preAnalyze(actx);
	}

	if(this->finallyStmt != nullptr){
		this->finallyStmt->setParent(this);
		this->finallyStmt->preAnalyze(actx);
	}
}

void TryStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->block->analyzeTypeRef(actx);

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		catchStmt->analyzeTypeRef(actx);
	}

	if(this->finallyStmt != nullptr){
		this->finallyStmt->analyzeTypeRef(actx);
	}
}

void TryStatement::analyze(AnalyzeContext* actx) {
	this->block->analyze(actx);

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		catchStmt->analyze(actx);
	}
}

void TryStatement::init(VirtualMachine* vm) {
	this->block->init(vm);

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);
		catchStmt->init(vm);
	}

	if(this->finallyStmt != nullptr){
		this->finallyStmt->init(vm);
	}
}

void TryStatement::interpret(VirtualMachine* vm) {
	this->block->interpret(vm);

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		catchStmt->interpret(vm);
	}

	if(this->finallyStmt != nullptr){
		this->finallyStmt->interpret(vm);
	}
}

bool TryStatement::hasCtrlStatement() const noexcept {
	return true;
}

int TryStatement::binarySize() const {
	checkNotNull(this->block);


	int total = sizeof(uint16_t);

	total += this->block->binarySize();

	total += sizeof(int32_t);
	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		total += catchStmt->binarySize();
	}


	return total;
}

void TryStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->block);

	out->putShort(CodeElement::STMT_TRY);

	this->block->toBinary(out);

	int maxLoop = this->catchStmts.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		catchStmt->toBinary(out);
	}
}

void TryStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::STMT_BLOCK);

	this->block = dynamic_cast<StatementBlock*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkKind(element, CodeElement::STMT_TRY_CATCH);

		CatchStatement* catchStmt = dynamic_cast<CatchStatement*>(element);
		this->catchStmts.addElement(catchStmt);
	}
}

void TryStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

void TryStatement::addCatchStatement(CatchStatement* catchStmt) noexcept {
	this->catchStmts.addElement(catchStmt);
}

} /* namespace alinous */
