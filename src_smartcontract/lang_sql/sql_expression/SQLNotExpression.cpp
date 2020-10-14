/*
 * SQLNotExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLNotExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "vm/VirtualMachine.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/logical/NotScanCondition.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_logical/NotScanColumnTarget.h"


using namespace alinous;

namespace alinous {

SQLNotExpression::SQLNotExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_NOT) {
	this->exp = nullptr;
}

SQLNotExpression::~SQLNotExpression() {
	delete this->exp;
}

void SQLNotExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLNotExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLNotExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_NOT);
	this->exp->toBinary(out);
}

void SQLNotExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

void SQLNotExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLNotExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLNotExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);
	if(!at.isBool()){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"Not expression requires boolean value.", {});
	}
}

AnalyzedType SQLNotExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLNotExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLNotExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	NotScanCondition* cond = new NotScanCondition();

	planner->push(cond);

	this->exp->interpret(vm);

	AbstractScanConditionElement* element = planner->pop();
	AbstractScanCondition* inner = ScanConditionCast::toAbstractScanCondition(element, vm, this);

	cond->addCondition(inner);

	return nullptr;
}

void SQLNotExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	NotScanColumnTarget* cond = new NotScanColumnTarget();
	colHolder->push(cond);

	this->exp->onSelectTarget(vm);

	AbstractScanColumnsTarget* col = colHolder->pop();
	cond->setCond(col);
}

} /* namespace alinous */
