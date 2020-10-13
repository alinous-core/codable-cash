/*
 * SqlMultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SqlMultiplicativeExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "scan_select/scan_planner/SelectScanPlanner.h"
#include "scan_select/scan_planner/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition_arithmetic/MultiplicativeScanCondition.h"
#include "scan_select/scan_condition/AbstractScanConditionElement.h"
#include "scan_select/scan_condition/IValueProvider.h"
#include "scan_select/scan_condition/ScanConditionCast.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns_arithmetic/MultiplicativeExpressionScanColumnTarget.h"

using codablecash::AbstractScanConditionElement;
using codablecash::IValueProvider;
using codablecash::ScanConditionCast;
using codablecash::SelectScanPlanner;

namespace alinous {

SqlMultiplicativeExpression::SqlMultiplicativeExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_MULTIPLICATIVE), operations(4) {
}

SqlMultiplicativeExpression::~SqlMultiplicativeExpression() {
}

void SqlMultiplicativeExpression::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

int SqlMultiplicativeExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractSQLBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}
	return total;
}

void SqlMultiplicativeExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_MULTIPLICATIVE);
	AbstractSQLBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void SqlMultiplicativeExpression::fromBinary(ByteBuffer* in) {
	AbstractSQLBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

void SqlMultiplicativeExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SqlMultiplicativeExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SqlMultiplicativeExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->analyze(actx);
	}
}

AnalyzedType SqlMultiplicativeExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_LONG);
}

void SqlMultiplicativeExpression::init(VirtualMachine* vm) {
	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* SqlMultiplicativeExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	MultiplicativeScanCondition* cond = new MultiplicativeScanCondition();

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

void SqlMultiplicativeExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	MultiplicativeExpressionScanColumnTarget* cond = new MultiplicativeExpressionScanColumnTarget();
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
