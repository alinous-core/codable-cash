/*
 * SQLAdditiveExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLAdditiveExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "scan_select/scan_planner/SelectScanPlanner.h"
#include "scan_select/scan_planner/ConditionsHolderStackMarker.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_condition_arithmetic/AdditiveScanCondition.h"

#include "scan_select/scan_condition/AbstractScanConditionElement.h"
#include "scan_select/scan_condition/ScanConditionCast.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_arithmetic/AdditiveExpressionScanColumnTarget.h"


using namespace codablecash;

namespace alinous {

SQLAdditiveExpression::SQLAdditiveExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_ADDITIVE), operations(4) {
}

SQLAdditiveExpression::~SQLAdditiveExpression() {
}

void SQLAdditiveExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int SQLAdditiveExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}
	return total;
}

void SQLAdditiveExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_ADDITIVE);
	AbstractSQLBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void SQLAdditiveExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}
/*
void SQLAdditiveExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SQLAdditiveExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SQLAdditiveExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyze(actx);
	}
}
*/
AnalyzedType SQLAdditiveExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_LONG);
}
/*
void SQLAdditiveExpression::init(VirtualMachine* vm) {
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);
		exp->init(vm);
	}
}*/


AbstractVmInstance* SQLAdditiveExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	AdditiveScanCondition* cond = new AdditiveScanCondition();

	planner->push(cond);

	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->interpret(vm);

		AbstractScanConditionElement* l = planner->pop();
		IValueProvider* vp = ScanConditionCast::toIValueProvider(l, vm, this);

		cond->addOperand(vp);
	}

	maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);

		cond->addOperator(op);
	}

	return nullptr;
}

void SQLAdditiveExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	AdditiveExpressionScanColumnTarget* cond = new AdditiveExpressionScanColumnTarget();
	colHolder->push(cond);

	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->onSelectTarget(vm);

		AbstractScanColumnsTarget* col = colHolder->pop();
		cond->addOperand(col);
	}

	maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);

		cond->addOperator(op);
	}
}


} /* namespace alinous */
