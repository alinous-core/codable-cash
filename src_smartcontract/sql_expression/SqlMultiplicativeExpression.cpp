/*
 * SqlMultiplicativeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SqlMultiplicativeExpression.h"

#include "sc_analyze/AnalyzedType.h"
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
	return nullptr; // FIXME SqlMultiplicativeExpression
}


} /* namespace alinous */
