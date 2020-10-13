/*
 * AbstractBinaryExpression.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "lang/sc_expression/AbstractBinaryExpression.h"

namespace alinous {

AbstractBinaryExpression::AbstractBinaryExpression(int kind) : AbstractExpression(kind) {
}

AbstractBinaryExpression::~AbstractBinaryExpression() {
	this->list.deleteElements();
}

void AbstractBinaryExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void AbstractBinaryExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		exp->analyzeTypeRef(actx);
	}
}


void AbstractBinaryExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		exp->analyze(actx);
	}
}

void AbstractBinaryExpression::init(VirtualMachine* vm) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		exp->init(vm);
	}
}

void AbstractBinaryExpression::addExp(AbstractExpression* exp) noexcept {
	this->list.addElement(exp);
}

int AbstractBinaryExpression::binarySize() const {
	int total = sizeof(uint32_t);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		total += exp->binarySize();
	}

	return total;
}

void AbstractBinaryExpression::toBinary(ByteBuffer* out) {
	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		exp->toBinary(out);
	}
}

void AbstractBinaryExpression::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsExp(element);
		AbstractExpression* exp = dynamic_cast<AbstractExpression*>(element);

		this->list.addElement(exp);
	}
}

} /* namespace alinous */
