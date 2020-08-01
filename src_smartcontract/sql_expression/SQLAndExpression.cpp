/*
 * SQLAndExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLAndExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "scan_condition_arithmetic/AdditiveScanCondition.h"

#include "scan_planner/SelectScanPlanner.h"

#include "vm/VirtualMachine.h"

#include "scan_condition/ScanConditionCast.h"

using namespace codablecash;

namespace alinous {

SQLAndExpression::SQLAndExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_AND) {
}

SQLAndExpression::~SQLAndExpression() {
}

int SQLAndExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	return total;
}

void SQLAndExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_AND);
	AbstractSQLBinaryExpression::toBinary(out);
}

void SQLAndExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);
}
/*
void SQLAndExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SQLAndExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SQLAndExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyze(actx);
	}
}*/

AnalyzedType SQLAndExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}
/*
void SQLAndExpression::init(VirtualMachine* vm) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->init(vm);
	}
}*/

AbstractVmInstance* SQLAndExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();

	AdditiveScanCondition* cond = new AdditiveScanCondition();
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


} /* namespace alinous */
