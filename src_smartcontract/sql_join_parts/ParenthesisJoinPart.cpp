/*
 * ParenthesisJoinPart.cpp
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#include "sql_join_parts/ParenthesisJoinPart.h"

#include "sc_analyze/AnalyzedType.h"


namespace alinous {

ParenthesisJoinPart::ParenthesisJoinPart() : AbstractJoinPart(CodeElement::SQL_EXP_PARENTHESIS_JOIN_PART) {
	this->part = nullptr;
}

ParenthesisJoinPart::~ParenthesisJoinPart() {
	delete this->part;
}

void ParenthesisJoinPart::setPart(AbstractJoinPart* part) noexcept {
	this->part = part;
}

int ParenthesisJoinPart::binarySize() const {
	checkNotNull(this->part);

	int total = sizeof(uint16_t);
	total += this->part->binarySize();

	return total;
}

void ParenthesisJoinPart::toBinary(ByteBuffer* out) {
	checkNotNull(this->part);

	out->putShort(CodeElement::SQL_EXP_PARENTHESIS_JOIN_PART);
	this->part->toBinary(out);
}

void ParenthesisJoinPart::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsJoinPart(element);
	this->part = dynamic_cast<AbstractJoinPart*>(element);
}

void ParenthesisJoinPart::preAnalyze(AnalyzeContext* actx) {
	this->part->setParent(this);
	this->part->preAnalyze(actx);
}

void ParenthesisJoinPart::analyzeTypeRef(AnalyzeContext* actx) {
	this->part->analyzeTypeRef(actx);
}

void ParenthesisJoinPart::analyze(AnalyzeContext* actx) {
	this->part->analyze(actx);
}

AnalyzedType ParenthesisJoinPart::getType(AnalyzeContext* actx) {
	return this->part->getType(actx);
}

void ParenthesisJoinPart::init(VirtualMachine* vm) {
	this->part->init(vm);
}

AbstractVmInstance* ParenthesisJoinPart::interpret(VirtualMachine* vm) {
	return this->part->interpret(vm);
}


} /* namespace alinous */
