/*
 * ForStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement_ctrl/ForStatement.h"
#include "lang/sc_expression/AbstractExpression.h"

#include "lang/sc_statement/StatementBlock.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_ctrl/BlockState.h"
#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "engine/sc_analyze_stack/AnalyzeStackPopper.h"
#include "engine/sc_analyze_stack/AnalyzeStackManager.h"

#include "vm/stack/StackPopper.h"

#include "instance/instance_exception/ExceptionInterrupt.h"

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
		this->bctrl = this->bctrl || this->stmt->hasCtrlStatement()
				|| (this->initStatement != nullptr && this->initStatement->hasCtrlStatement())
				|| (this->cond != nullptr && this->cond->throwsException())
				|| (this->postLoop != nullptr && this->postLoop->hasCtrlStatement());
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
	StackFloatingVariableHandler releaser(gc);
	ExecControlManager* ctrl = vm->getCtrl();

	if(this->initStatement != nullptr){
		this->initStatement->interpret(vm);

		if(ctrl->isExceptionThrown()){
			return;
		}
	}

	while(true){
		if(this->cond != nullptr){
			try{
				inst = this->cond->interpret(vm);
				releaser.registerInstance(inst);
			}
			catch(ExceptionInterrupt* e){
				delete e;
				break;
			}

			ref = dynamic_cast<PrimitiveReference*>(inst);

			bool exec = ref->getBoolValue();
			if(!exec){
				break;
			}
		}

		if(this->stmt != nullptr){
			this->stmt->interpret(vm);

			int stat = ctrl->checkStatementCtrl(this->blockState, this->stmt);
			if(stat == AbstractCtrlInstruction::RET_BREAK || stat == AbstractCtrlInstruction::RET_THROW){
				break;
			}
		}

		if(this->postLoop != nullptr){
			this->postLoop->interpret(vm);

			if(ctrl->isExceptionThrown()){
				break;
			}
		}

	}
}

bool ForStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

bool ForStatement::hasConstructor() const noexcept {
	bool ret = this->stmt->hasConstructor();

	if(this->initStatement != nullptr){
		ret = ret || this->initStatement->hasConstructor();
	}
	if(this->postLoop != nullptr){
		ret = ret || this->postLoop->hasConstructor();
	}
	return ret;
}

} /* namespace alinous */
