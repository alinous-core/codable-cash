/*
 * SQLOrExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLOrExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/SelectScanPlanner.h"

#include "scan_condition_logical/OrScanCondition.h"

#include "scan_condition/ScanConditionCast.h"

namespace alinous {

SQLOrExpression::SQLOrExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_OR) {
}

SQLOrExpression::~SQLOrExpression() {
}

int SQLOrExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	return total;
}

void SQLOrExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_OR);
	AbstractSQLBinaryExpression::toBinary(out);
}

void SQLOrExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);
}

void SQLOrExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SQLOrExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SQLOrExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyze(actx);
	}
}

void SQLOrExpression::init(VirtualMachine* vm) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* SQLOrExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();

	OrScanCondition* cond = new OrScanCondition();
	planner->push(cond);

	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->interpret(vm);

		AbstractScanConditionElement* element = planner->pop();
		AbstractScanCondition* inner = ScanConditionCast::toAbstractScanCondition(element, vm, this);

		cond->addCondition(inner);
	}

	return nullptr;
}

AnalyzedType SQLOrExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLOrExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();

	// FIXME onSelectTarget();
}

} /* namespace alinous */
