/*
 * SQLIsNullExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLIsNullExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "scan_select/scan_condition/exp/IsNullScanCondition.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_exp/IsNullScanColumnTarget.h"


namespace alinous {

SQLIsNullExpression::SQLIsNullExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_IS_NULL) {
	this->exp = nullptr;
	this->notnull = false;
}

SQLIsNullExpression::~SQLIsNullExpression() {
	delete this->exp;
}

void SQLIsNullExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLIsNullExpression::setNotNull(bool notnull) noexcept {
	this->notnull = notnull;
}

int SQLIsNullExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void SQLIsNullExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_IS_NULL);
	this->exp->toBinary(out);
	out->put(this->notnull ? 1 : 0);
}

void SQLIsNullExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);

	int8_t bl = in->get();
	this->notnull = (bl == 1);
}

void SQLIsNullExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLIsNullExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLIsNullExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

AnalyzedType SQLIsNullExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLIsNullExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLIsNullExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	IsNullScanCondition* cond = new IsNullScanCondition();

	planner->push(cond);

	this->exp->interpret(vm);

	AbstractScanConditionElement* element = planner->pop();
	IValueProvider* inner = ScanConditionCast::toIValueProvider(element, vm, this);

	cond->setCondition(inner);
	cond->setIsNull(this->notnull);

	return nullptr;
}

void SQLIsNullExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	IsNullScanColumnTarget* cond = new IsNullScanColumnTarget();
	colHolder->push(cond);

	this->exp->onSelectTarget(vm);

	AbstractScanColumnsTarget* col = colHolder->pop();
	cond->setCondition(col);
	cond->setIsNull(this->notnull);
}

} /* namespace alinous */
