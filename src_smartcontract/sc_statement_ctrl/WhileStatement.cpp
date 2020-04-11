/*
 * WhileStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/WhileStatement.h"
#include "sc_expression/AbstractExpression.h"

#include "sc_statement/StatementBlock.h"

#include "vm_ctrl/BlockState.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/ValidationError.h"

#include "instance_ref/PrimitiveReference.h"

#include "instance_gc/GcManager.h"

#include "vm_ctrl/ExecControlManager.h"

#include "vm_ctrl/AbstractCtrlInstruction.h"
namespace alinous {

WhileStatement::WhileStatement() : AbstractStatement(CodeElement::STMT_WHILE) {
	this->exp = nullptr;
	this->stmt = nullptr;
	this->blockState = new BlockState(BlockState::BLOCK_WHILE);
	this->bctrl = false;
}

WhileStatement::~WhileStatement() {
	delete this->exp;
	delete this->stmt;
	delete this->blockState;
}

void WhileStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);

	this->stmt->setParent(this);
	this->stmt->preAnalyze(actx);

	StatementBlock* block = dynamic_cast<StatementBlock*>(this->stmt);
	if(block != nullptr){
		block->setBlockState(new BlockState(BlockState::BLOCK_CTRL_LOOP));
	}
}

void WhileStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
	this->stmt->analyzeTypeRef(actx);
}

void WhileStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
	this->stmt->analyze(actx);

	AnalyzedType atype = this->exp->getType(actx);
	uint8_t type = atype.getType();
	if(type != AnalyzedType::TYPE_BOOL){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"While's expression requires boolean parameter.", {});
	}

	this->bctrl = this->bctrl || this->exp->throwsException() || this->stmt->hasCtrlStatement();
}

void WhileStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void WhileStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

int WhileStatement::binarySize() const {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += this->stmt->binarySize();

	return total;
}

void WhileStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	out->putShort(CodeElement::STMT_WHILE);
	this->exp->toBinary(out);
	this->stmt->toBinary(out);
}

void WhileStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);
}

void WhileStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
	this->stmt->init(vm);
}

void WhileStatement::interpret(VirtualMachine* vm) {
	AbstractVmInstance* inst = nullptr;
	PrimitiveReference* ref = nullptr;

	GcManager* gc = vm->getGc();
	ExecControlManager* ctrl = vm->getCtrl();

	while(true){
		inst = this->exp->interpret(vm);
		ref = dynamic_cast<PrimitiveReference*>(inst);

		bool exec = ref->getBoolValue();
		gc->handleFloatingObject(ref);

		if(!exec){
			break;
		}

		this->stmt->interpret(vm);

		// control
		int stat = ctrl->checkStatementCtrl(this->blockState, stmt);
		if(stat == AbstractCtrlInstruction::RET_BREAK){
			break;
		}
	}
}

bool WhileStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

} /* namespace alinous */
