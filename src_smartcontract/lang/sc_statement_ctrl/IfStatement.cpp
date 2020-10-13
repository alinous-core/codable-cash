/*
 * IfStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement_ctrl/IfStatement.h"
#include "lang/sc_expression/AbstractExpression.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "vm/VirtualMachine.h"

#include "engine/sc_analyze/AnalyzeContext.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "vm/vm_ctrl/ExecControlManager.h"

#include "instance/instance_exception/ExceptionInterrupt.h"


namespace alinous {

IfStatement::IfStatement() : AbstractStatement(CodeElement::STMT_IF) {
	this->exp = nullptr;
	this->stmt = nullptr;

	this->elseStmt = nullptr;

	this->bctrl = false;
}

IfStatement::~IfStatement() {
	delete this->exp;
	delete this->stmt;

	this->list.deleteElements();

	delete this->elseStmt;
}

void IfStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);

	this->stmt->setParent(this);
	this->stmt->preAnalyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		stmt->setParent(this);
		stmt->preAnalyze(actx);
	}

	if(this->elseStmt != nullptr){
		this->elseStmt->setParent(this);
		this->elseStmt->preAnalyze(actx);
	}
}

void IfStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
	this->stmt->analyzeTypeRef(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		stmt->analyzeTypeRef(actx);
	}

	if(this->elseStmt != nullptr){
		this->elseStmt->analyzeTypeRef(actx);
	}
}

void IfStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
	this->stmt->analyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		stmt->analyze(actx);
	}

	if(this->elseStmt != nullptr){
		this->elseStmt->analyze(actx);
	}

	AnalyzedType at = this->exp->getType(actx);
	if(!at.isBool()){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"If's expression requires boolean parameter.", {});
	}

	maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		at = stmt->exp->getType(actx);
		if(!at.isBool()){
			actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"If's expression requires boolean parameter.", {});
		}
	}

	// bctrl
	this->bctrl = this->bctrl || this->stmt->hasCtrlStatement();

	maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		this->bctrl = this->bctrl || stmt->hasCtrlStatement();
	}
	if(this->elseStmt != nullptr){
		this->bctrl = this->bctrl || this->elseStmt->hasCtrlStatement();
	}
}

void IfStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void IfStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

void IfStatement::addElseIf(IfStatement* elseif) noexcept {
	this->list.addElement(elseif);
}

void IfStatement::setElseStatement(AbstractStatement* elseStmt) noexcept {
	this->elseStmt = elseStmt;
}

int IfStatement::binarySize() const {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += this->stmt->binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; i++){
		IfStatement* ifstmt = this->list.get(i);
		total += ifstmt->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->elseStmt != nullptr){
		total += this->elseStmt->binarySize();
	}

	return total;
}

void IfStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	out->putShort(CodeElement::STMT_IF);
	this->exp->toBinary(out);
	this->stmt->toBinary(out);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; i++){
		IfStatement* ifstmt = this->list.get(i);
		ifstmt->toBinary(out);
	}

	bool bl = this->elseStmt != nullptr;
	out->put(bl ? 1 : 0);
	if(bl){
		this->elseStmt->toBinary(out);
	}
}

void IfStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkKind(element, CodeElement::STMT_IF);

		IfStatement* ifStmt = dynamic_cast<IfStatement*>(element);
		addElseIf(ifStmt);
	}

	uint8_t bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkIsStatement(element);
		this->elseStmt = dynamic_cast<AbstractStatement*>(element);
	}
}

void IfStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
	this->stmt->init(vm);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);
		stmt->init(vm);
	}

	if(this->elseStmt != nullptr){
		this->elseStmt->init(vm);
	}
}

void IfStatement::interpret(VirtualMachine* vm) {
	ExecControlManager* ctrl = vm->getCtrl();

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* expV = nullptr;

	try{
		expV = releaser.registerInstance(this->exp->interpret(vm));
	}
	catch(ExceptionInterrupt* e){
		delete e;
		return;
	}

	PrimitiveReference* condition = dynamic_cast<PrimitiveReference*>(expV);

	if(condition->getBoolValue()){
		this->stmt->interpret(vm);
		return;
	}

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		try{
			expV = releaser.registerInstance(stmt->exp->interpret(vm));
		}
		catch(ExceptionInterrupt* e){
			delete e;
			return;
		}

		condition = dynamic_cast<PrimitiveReference*>(expV);

		if(condition->getBoolValue()){
			stmt->stmt->interpret(vm);
			return;
		}
	}

	if(this->elseStmt != nullptr){
		this->elseStmt->interpret(vm);
	}
}

bool IfStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

bool IfStatement::hasConstructor() const noexcept {
	bool ret = this->stmt->hasConstructor();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IfStatement* stmt = this->list.get(i);

		ret = ret || stmt->hasConstructor();
	}

	if(this->elseStmt != nullptr){
		ret = ret || this->elseStmt->hasConstructor();
	}

	return ret;
}

} /* namespace alinous */
