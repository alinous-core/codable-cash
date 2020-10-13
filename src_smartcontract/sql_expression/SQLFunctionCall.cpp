/*
 * SQLFunctionCall.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "sql_expression/SQLFunctionCall.h"
#include "sc_expression/VariableIdentifier.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_condition_exp/FunctionCallScanCondition.h"

#include "scan_select/scan_condition/ScanConditionCast.h"

#include "scan_select/scan_planner/SelectScanPlanner.h"
#include "scan_select/scan_planner/ConditionsHolderStackMarker.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns_exp/FunctionCallScanColumnTarget.h"


namespace alinous {

SQLFunctionCall::SQLFunctionCall() : AbstractSQLExpression(CodeElement::SQL_EXP_FUNCTION_CALL) {
	this->name = nullptr;
}

SQLFunctionCall::~SQLFunctionCall() {
	delete this->name;
	this->arguments.deleteElements();
}

void SQLFunctionCall::setName(VariableIdentifier* name) noexcept {
	this->name = name;
}

void SQLFunctionCall::addArgument(AbstractSQLExpression* arg) noexcept {
	this->arguments.addElement(arg);
}

int SQLFunctionCall::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += this->name->binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);
		total += exp->binarySize();
	}

	return total;
}

void SQLFunctionCall::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::SQL_EXP_FUNCTION_CALL);
	this->name->toBinary(out);

	int maxLoop = this->arguments.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);
		exp->toBinary(out);
	}
}

void SQLFunctionCall::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);
	this->name = dynamic_cast<VariableIdentifier*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkIsSQLExp(element);
		AbstractSQLExpression* exp = dynamic_cast<AbstractSQLExpression*>(element);

		this->arguments.addElement(exp);
	}
}

void SQLFunctionCall::preAnalyze(AnalyzeContext* actx) {
	this->name->setParent(this);
	this->name->preAnalyze(actx);

	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SQLFunctionCall::analyzeTypeRef(AnalyzeContext* actx) {
	this->name->analyzeTypeRef(actx);

	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SQLFunctionCall::analyze(AnalyzeContext* actx) {
	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);

		exp->analyze(actx);
	}
}

AnalyzedType SQLFunctionCall::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void alinous::SQLFunctionCall::init(VirtualMachine* vm) {
	this->name->init(vm);

	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* SQLFunctionCall::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	FunctionCallScanCondition* cond = new FunctionCallScanCondition();
	planner->push(cond);

	const UnicodeString* n = this->name->getName();
	cond->setName(new UnicodeString(n));

	AbstractScanConditionElement* element = nullptr;
	IValueProvider* val = nullptr;

	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);

		exp->interpret(vm);

		element = planner->pop();
		val = ScanConditionCast::toIValueProvider(element, vm, this);
		cond->addArgument(val);
	}

	return nullptr;
}

void SQLFunctionCall::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	FunctionCallScanColumnTarget* cond = new FunctionCallScanColumnTarget();
	colHolder->push(cond);

	const UnicodeString* n = this->name->getName();
	cond->setName(n);

	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->arguments.get(i);

		exp->onSelectTarget(vm);

		AbstractScanColumnsTarget* col = colHolder->pop();
		cond->addArgument(col);
	}
}

} /* namespace alinous */
