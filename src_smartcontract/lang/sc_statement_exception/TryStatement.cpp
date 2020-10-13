/*
 * TryStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "lang/sc_statement_exception/TryStatement.h"

#include "lang/sc_statement/StatementBlock.h"
#include "lang/sc_statement_exception/CatchStatement.h"
#include "lang/sc_statement_exception/FinallyStatement.h"

#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/AbstractCtrlInstruction.h"
#include "vm/vm_ctrl/BlockState.h"

#include "vm/VirtualMachine.h"


namespace alinous {

TryStatement::TryStatement() : AbstractStatement(CodeElement::STMT_TRY) {
	this->block = nullptr;
	this->finallyStmt = nullptr;
	this->bctrl = false;
	this->blockState = new BlockState(BlockState::BLOCK_NORMAL);
}

TryStatement::~TryStatement() {
	delete this->block;
	this->catchStmts.deleteElements();
	delete this->finallyStmt;
	delete this->blockState;
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
	this->bctrl = this->block->hasCtrlStatement();

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		catchStmt->analyze(actx);
		this->bctrl = this->bctrl || catchStmt->hasCtrlStatement();
	}

	if(this->finallyStmt != nullptr){
		this->finallyStmt->analyze(actx);
		this->bctrl = this->bctrl || this->finallyStmt->hasCtrlStatement();
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

	ExecControlManager* ctrl = vm->getCtrl();
	if(ctrl->isExceptionThrown()){
		int maxLoop = this->catchStmts.size();
		for(int i = 0; i != maxLoop; ++i){
			CatchStatement* catchStmt = this->catchStmts.get(i);

			catchStmt->interpret(vm);

			if(vm->isCaught()){
				break;
			}
		}
	}


	if(this->finallyStmt != nullptr){
		this->finallyStmt->interpret(vm);
	}
}

bool TryStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
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

	total += sizeof(int8_t);
	bool bl = this->finallyStmt != nullptr;
	if(bl){
		total += this->finallyStmt->binarySize();
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

	bool bl = this->finallyStmt != nullptr;
	out->put(bl ? 1 : 0);
	if(bl){
		this->finallyStmt->toBinary(out);
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

	int8_t bl = in->get();
	if(bl == 1){
		 element = createFromBinary(in);
		 checkKind(element, CodeElement::STMT_FINALLY);

		 this->finallyStmt = dynamic_cast<FinallyStatement*>(element);
	}
}

void TryStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

void TryStatement::addCatchStatement(CatchStatement* catchStmt) noexcept {
	this->catchStmts.addElement(catchStmt);
}

bool TryStatement::hasConstructor() const noexcept {
	bool ret = this->block->hasConstructor();

	int maxLoop = this->catchStmts.size();
	for(int i = 0; i != maxLoop; ++i){
		CatchStatement* catchStmt = this->catchStmts.get(i);

		ret = ret || catchStmt->hasConstructor();
	}

	if(this->finallyStmt != nullptr){
		ret = ret || this->finallyStmt->hasConstructor();
	}

	return ret;
}

void TryStatement::setFinallyStatement(FinallyStatement* finallyStmt) noexcept {
	this->finallyStmt = finallyStmt;
}

} /* namespace alinous */
