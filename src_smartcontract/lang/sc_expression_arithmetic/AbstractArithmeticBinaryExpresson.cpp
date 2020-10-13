/*
 * AbstractArithmeticBinaryExpresson.cpp
 *
 *  Created on: 2020/03/05
 *      Author: iizuka
 */

#include "lang/sc_expression_arithmetic/AbstractArithmeticBinaryExpresson.h"

#include "engine/sc_analyze/AnalyzeContext.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

AbstractArithmeticBinaryExpresson::AbstractArithmeticBinaryExpresson(int kind) : AbstractBinaryExpression(kind), operations(8) {
	this->atype = nullptr;
}

AbstractArithmeticBinaryExpresson::~AbstractArithmeticBinaryExpresson() {
	delete this->atype;
}

AnalyzedType AbstractArithmeticBinaryExpresson::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void AbstractArithmeticBinaryExpresson::addOpe(uint8_t ope) noexcept {
	this->operations.addElement(ope);
}

void AbstractArithmeticBinaryExpresson::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyzeTypeRef(actx);
}

void AbstractArithmeticBinaryExpresson::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	uint8_t type = AnalyzedType::TYPE_BYTE;
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		AnalyzedType at = exp->getType(actx);

		if(at.isPrimitiveInteger() && !at.isArray()){
			uint8_t t = at.getType();
			if(type < t){
				type = t;
			}
		}
		else {
			this->atype = new AnalyzedType(at);
			return;
		}
	}

	this->atype = new AnalyzedType(type);
}

int AbstractArithmeticBinaryExpresson::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->operations.size();
	for(int i = 0; i != maxLoop; ++i){
		total += sizeof(uint8_t);
	}

	return total;
}

void AbstractArithmeticBinaryExpresson::toBinary(ByteBuffer* out) {
	out->putShort(this->kind);
	AbstractBinaryExpression::toBinary(out);

	int maxLoop = this->operations.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = this->operations.get(i);
		out->put(op);
	}
}

void AbstractArithmeticBinaryExpresson::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		uint8_t op = in->get();
		this->operations.addElement(op);
	}
}

} /* namespace alinous */
