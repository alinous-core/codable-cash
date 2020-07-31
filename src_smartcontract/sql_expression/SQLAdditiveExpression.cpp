/*
 * SQLAdditiveExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLAdditiveExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionStackPopper.h"

#include "vm/VirtualMachine.h"

#include "scan_condition_logical/AndScanCondition.h"


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

	// FIXME SQLAdditiveExpression
	return nullptr;
}


} /* namespace alinous */
