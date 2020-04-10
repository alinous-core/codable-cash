/*
 * ForStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/ForStatement.h"
#include "sc_expression/AbstractExpression.h"

#include "sc_statement/StatementBlock.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

#include "instance_ref/PrimitiveReference.h"

#include "vm/VirtualMachine.h"

#include "vm_ctrl/BlockState.h"
#include "vm_ctrl/ExecControlManager.h"
#include "vm_ctrl/AbstractCtrlInstruction.h"

#include "instance_gc/GcManager.h"

#include "sc_analyze_stack/AnalyzeStackPopper.h"
#include "sc_analyze_stack/AnalyzeStackManager.h"

#include "stack/StackPopper.h"

namespace alinous {

ForStatement::ForStatement() : AbstractStatement(CodeElement::STMT_FOR) {
	this->stmt = nullptr;
	this->initStatement = nullptr;
	this->cond = nullptr;
	this->postLoop = nullptr;
	this->blockState = new BlockState(BlockState::BLOCK_FOR);
	this->bctrl = false;
}

ForStatement::~ForStatement() {
	delete this->stmt;
	delete this->initStatement;
	delete this->cond;
	delete this->postLoop;
	delete this->blockState;
}

void ForStatement::preAnalyze(AnalyzeContext* actx) {
	if(this->stmt != nullptr){
		this->stmt->setParent(this);
		this->stmt->preAnalyze(actx);

		StatementBlock* block = dynamic_cast<StatementBlock*>(this->stmt);
		if(block != nullptr){
			block->setBlockState(new BlockState(BlockState::BLOCK_CTRL_LOOP));
		}
	}
	if(this->initStatement != nullptr){
		this->initStatement->setParent(this);
		this->initStatement->preAnalyze(actx);
	}
	if(this->cond != nullptr){
		this->cond->setParent(this);
		this->cond->preAnalyze(actx);
	}
	if(this->postLoop != nullptr){
		this->postLoop->setParent(this);
		this->postLoop->preAnalyze(actx);
	}
}

void ForStatement::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->stmt != nullptr){
		this->stmt->analyzeTypeRef(actx);
	}
	if(this->initStatement != nullptr){
		this->initStatement->analyzeTypeRef(actx);
	}
	if(this->cond != nullptr){
		this->cond->analyzeTypeRef(actx);
	}
	if(this->postLoop != nullptr){
		this->postLoop->analyzeTypeRef(actx);
	}
}

void ForStatement::analyze(AnalyzeContext* actx) {
	AnalyzeStackManager* stackMgr = actx->getAnalyzeStackManager();
	AnalyzeStackPopper popper(stackMgr, false);
	stackMgr->addBlockStack();

	if(this->stmt != nullptr){
		this->stmt->analyze(actx);
	}

	if(this->initStatement != nullptr){
		this->initStatement->analyze(actx);
	}

	if(this->cond != nullptr){
		this->cond->analyze(actx);

		AnalyzedType atype = this->cond->getType(actx);
		uint8_t type = atype.getType();
		if(type != AnalyzedType::TYPE_BOOL){
			actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"For statement's expression requires boolean parameter.", {});
		}
	}
	if(this->postLoop != nullptr){
		this->postLoop->analyze(actx);
	}

	// bctrl
	if(this->stmt != nullptr){
		this->bctrl = this->bctrl || this->stmt->hasCtrlStatement();
	}
}

void ForStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

void ForStatement::setInit(AbstractStatement* initStatement) noexcept {
	this->initStatement = initStatement;
}

void ForStatement::setCondition(AbstractExpression* cond) noexcept {
	this->cond = cond;
}

void ForStatement::setPostLoop(AbstractStatement* postLoop) noexcept {
	this->postLoop = postLoop;
}

int ForStatement::binarySize() const {
	checkNotNull(this->stmt);
	checkNotNull(this->initStatement);
	checkNotNull(this->cond);
	checkNotNull(this->postLoop);

	int total = sizeof(uint16_t);
	total += this->stmt->binarySize();
	total += this->initStatement->binarySize();
	total += this->cond->binarySize();
	total += this->postLoop->binarySize();

	return total;
}

void ForStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->stmt);
	checkNotNull(this->initStatement);
	checkNotNull(this->cond);
	checkNotNull(this->postLoop);

	out->putShort(CodeElement::STMT_FOR);
	this->stmt->toBinary(out);
	this->initStatement->toBinary(out);
	this->cond->toBinary(out);
	this->postLoop->toBinary(out);
}

void ForStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->initStatement = dynamic_cast<AbstractStatement*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->cond = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->postLoop = dynamic_cast<AbstractStatement*>(element);
}

void ForStatement::init(VirtualMachine* vm) {
	if(this->stmt != nullptr){
		this->stmt->init(vm);
	}
	if(this->initStatement != nullptr){
		this->initStatement->init(vm);
	}
	if(this->cond != nullptr){
		this->cond->init(vm);
	}
	if(this->postLoop != nullptr){
		this->postLoop->init(vm);
	}
}


void ForStatement::interpret(VirtualMachine* vm) {
	vm->newStack();
	StackPopper stackPopper(vm);

	AbstractVmInstance* inst = nullptr;
	PrimitiveReference* ref = nullptr;

	GcManager* gc = vm->getGc();
	ExecControlManager* ctrl = vm->getCtrl();

	if(this->initStatement != nullptr){
		this->initStatement->interpret(vm);
	}

	while(true){
		if(this->cond != nullptr){
			inst = this->cond->interpret(vm);
			ref = dynamic_cast<PrimitiveReference*>(inst);

			bool exec = ref->getBoolValue();
			gc->handleFloatingObject(ref);

			if(!exec){
				break;
			}
		}

		if(this->stmt != nullptr){
			this->stmt->interpret(vm);

			int stat = ctrl->checkStatementCtrl(this->blockState, this->stmt);
			if(stat == AbstractCtrlInstruction::RET_BREAK){
				return;
			}
		}

		if(this->postLoop != nullptr){
			this->postLoop->interpret(vm);
		}

	}
}

bool ForStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

} /* namespace alinous */
