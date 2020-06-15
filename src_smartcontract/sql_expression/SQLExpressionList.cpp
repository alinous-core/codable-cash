/*
 * SQLExpressionList.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLExpressionList.h"

#include "sc_analyze/AnalyzedType.h"


namespace alinous {

SQLExpressionList::SQLExpressionList() : AbstractSQLExpression(CodeElement::SQL_EXP_EXP_LIST) {
}

SQLExpressionList::~SQLExpressionList() {
	this->list.deleteElements();
}

void SQLExpressionList::addExpression(AbstractSQLExpression* exp) noexcept {
	this->list.addElement(exp);
}

int SQLExpressionList::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);
		total += exp->binarySize();
	}

	return total;
}

void SQLExpressionList::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_EXP_LIST);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);
		exp->toBinary(out);
	}
}

void SQLExpressionList::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		AbstractSQLExpression* exp = dynamic_cast<AbstractSQLExpression*>(element);

		this->list.addElement(exp);
	}
}

void SQLExpressionList::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SQLExpressionList::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SQLExpressionList::analyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->analyze(actx);
	}
}

AnalyzedType SQLExpressionList::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void SQLExpressionList::init(VirtualMachine* vm) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->init(vm);
	}
}



int SQLExpressionList::numExpressions() const noexcept {
	return this->list.size();
}


AbstractVmInstance* SQLExpressionList::interpret(VirtualMachine* vm) {
	return nullptr;
}


} /* namespace alinous */
