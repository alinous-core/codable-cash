/*
 * SQLBetweenExpression.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "sql_expression/SQLBetweenExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "scan_condition_exp/BetweenScanCondition.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/SelectScanPlanner.h"

using codablecash::BetweenScanCondition;

namespace alinous {

SQLBetweenExpression::SQLBetweenExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_BETWEEN) {
	this->left = nullptr;
	this->start = nullptr;
	this->end = nullptr;
}

SQLBetweenExpression::~SQLBetweenExpression() {
	delete this->left;
	delete this->start;
	delete this->end;
}

void SQLBetweenExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLBetweenExpression::setStart(AbstractSQLExpression* exp) noexcept {
	this->start = exp;
}

void SQLBetweenExpression::setEnd(AbstractSQLExpression* exp) noexcept {
	this->end = exp;
}

int SQLBetweenExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->start);
	checkNotNull(this->end);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->start->binarySize();
	total += this->end->binarySize();

	return total;
}

void SQLBetweenExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->start);
	checkNotNull(this->end);

	out->putShort(CodeElement::SQL_EXP_BETWEEN);
	this->left->toBinary(out);
	this->start->toBinary(out);
	this->end->toBinary(out);
}

void SQLBetweenExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->start = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->end = dynamic_cast<AbstractSQLExpression*>(element);
}

void SQLBetweenExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->start->setParent(this);
	this->start->preAnalyze(actx);

	this->end->setParent(this);
	this->end->preAnalyze(actx);
}

void SQLBetweenExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->start->analyzeTypeRef(actx);
	this->end->analyzeTypeRef(actx);
}

void SQLBetweenExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->start->analyze(actx);
	this->end->analyze(actx);
}

AnalyzedType SQLBetweenExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLBetweenExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->start->init(vm);
	this->end->init(vm);
}

AbstractVmInstance* SQLBetweenExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();

	BetweenScanCondition* cond = new BetweenScanCondition();
	planner->push(cond);

	return nullptr;
}


} /* namespace alinous */
