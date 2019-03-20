/*
 * AbstractSQLBinaryExpression.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

AbstractSQLBinaryExpression::AbstractSQLBinaryExpression(int kind) : AbstractSQLExpression(kind) {
}

AbstractSQLBinaryExpression::~AbstractSQLBinaryExpression() {
	this->operands.deleteElements();
}

void AbstractSQLBinaryExpression::addOperand(AbstractSQLExpression* exp) noexcept {
	this->operands.addElement(exp);
}

int AbstractSQLBinaryExpression::binarySize() const {
	int total = sizeof(uint32_t);

	int maxLoop = this->operands.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);
		total += exp->binarySize();
	}

	return total;
}

void AbstractSQLBinaryExpression::toBinary(ByteBuffer* out) {
	int maxLoop = this->operands.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->operands.get(i);
		exp->toBinary(out);
	}

}

void AbstractSQLBinaryExpression::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		AbstractSQLExpression* exp = dynamic_cast<AbstractSQLExpression*>(element);
		this->operands.addElement(exp);
	}
}

} /* namespace alinous */
