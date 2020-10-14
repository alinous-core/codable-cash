/*
 * SQLParenthesisExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLParenthesisExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/exp/ParenthesisScanCondition.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_exp/ParenthesisScanColumnTarget.h"


using codablecash::ParenthesisScanCondition;
using codablecash::SelectScanPlanner;

namespace alinous {

SQLParenthesisExpression::SQLParenthesisExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_PARENTHESIS) {
	this->exp = nullptr;
}

SQLParenthesisExpression::~SQLParenthesisExpression() {
	delete this->exp;
}

void SQLParenthesisExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLParenthesisExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLParenthesisExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_PARENTHESIS);
	this->exp->toBinary(out);
}

void SQLParenthesisExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

void SQLParenthesisExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLParenthesisExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLParenthesisExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

AnalyzedType SQLParenthesisExpression::getType(AnalyzeContext* actx) {
	return this->exp->getType(actx);
}

void SQLParenthesisExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLParenthesisExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	ParenthesisScanCondition* cond = new ParenthesisScanCondition();
	planner->push(cond);

	this->exp->interpret(vm);

	AbstractScanConditionElement* element = planner->pop();
	AbstractScanCondition* inner = ScanConditionCast::toAbstractScanCondition(element, vm, this);

	cond->addCondition(inner);


	return nullptr;
}

void SQLParenthesisExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	ParenthesisScanColumnTarget* cond = new ParenthesisScanColumnTarget();
	colHolder->push(cond);

	this->exp->onSelectTarget(vm);

	AbstractScanColumnsTarget* col = colHolder->pop();
	cond->setInnser(col);
}

} /* namespace alinous */
