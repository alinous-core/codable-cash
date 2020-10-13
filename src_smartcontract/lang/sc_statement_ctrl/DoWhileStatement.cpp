/*
 * DoWhileStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement_ctrl/DoWhileStatement.h"
#include "lang/sc_expression/AbstractExpression.h"

#include "lang/sc_statement/StatementBlock.h"

#include "vm/vm_ctrl/BlockState.h"
#include "vm/vm_ctrl/ExecControlManager.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "vm/VirtualMachine.h"

#include "vm/vm_ctrl/AbstractCtrlInstruction.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_exception/ExceptionInterrupt.h"


namespace alinous {

DoWhileStatement::DoWhileStatement() : AbstractStatement(CodeElement::STMT_DO_WHILE) {
	this->exp = nullptr;
	this->stmt = nullptr;
	this->blockState = new BlockState(BlockState::BLOCK_DO_WHILE);
	this->bctrl = false;
}

DoWhileStatement::~DoWhileStatement() {
	delete this->exp;
	delete this->stmt;
	delete this->blockState;
}

void DoWhileStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);

	this->stmt->setParent(this);
	this->stmt->preAnalyze(actx);

	StatementBlock* block = dynamic_cast<StatementBlock*>(this->stmt);
	if(block != nullptr){
		block->setBlockState(new BlockState(BlockState::BLOCK_CTRL_LOOP));
	}
}

void DoWhileStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
	this->stmt->analyzeTypeRef(actx);
}


void alinous::DoWhileStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
	this->stmt->analyze(actx);

	AnalyzedType atype = this->exp->getType(actx);
	uint8_t type = atype.getType();
	if(type != AnalyzedType::TYPE_BOOL){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"Do While statement's expression requires boolean parameter.", {});
	}

	if(this->exp->throwsException() || this->stmt->hasCtrlStatement()){
		this->bctrl = true;
	}
}

void DoWhileStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void DoWhileStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

int DoWhileStatement::binarySize() const {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += this->stmt->binarySize();

	return total;
}

void DoWhileStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	out->putShort(CodeElement::STMT_DO_WHILE);
	this->exp->toBinary(out);
	this->stmt->toBinary(out);
}

void DoWhileStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);
}

void DoWhileStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
	this->stmt->init(vm);
}

void DoWhileStatement::interpret(VirtualMachine* vm) {
	AbstractVmInstance* inst = nullptr;
	PrimitiveReference* ref = nullptr;

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);
	ExecControlManager* ctrl = vm->getCtrl();

	int loopCount = 0;
	while(true){
		this->stmt->interpret(vm);

		// control
		int stat = ctrl->checkStatementCtrl(this->blockState, stmt);
		if(stat == AbstractCtrlInstruction::RET_BREAK || stat == AbstractCtrlInstruction::RET_THROW){
			break;
		}

		// check
		try{
			inst = this->exp->interpret(vm);
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

		if(loopCount == 10){
			releaser.release();
			loopCount = 0;
		}
		else{
			loopCount++;
		}
	}
}

bool DoWhileStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

bool DoWhileStatement::hasConstructor() const noexcept {
	return this->stmt->hasConstructor();
}

} /* namespace alinous */
