/*
 * SQLNullLiteral.cpp
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLNullLiteral.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

namespace alinous {

SQLNullLiteral::SQLNullLiteral() : AbstractSQLExpression(CodeElement::SQL_EXP_NULL_LITERAL){

}

SQLNullLiteral::~SQLNullLiteral() {

}

int SQLNullLiteral::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void SQLNullLiteral::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_NULL_LITERAL);
}

void SQLNullLiteral::fromBinary(ByteBuffer* in) {
}

void SQLNullLiteral::preAnalyze(AnalyzeContext* actx) {
}

void SQLNullLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}

void SQLNullLiteral::analyze(AnalyzeContext* actx) {
}

AnalyzedType SQLNullLiteral::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_NULL);
}

void SQLNullLiteral::init(VirtualMachine* vm) {
}

AbstractVmInstance* SQLNullLiteral::interpret(VirtualMachine* vm) {
	if(vm->isSelectPlanning()) {
		interpretOnPlanning(vm);
		return nullptr;
	}

	return nullptr;
}

void SQLNullLiteral::onSelectTarget(VirtualMachine* vm) {
}

void SQLNullLiteral::interpretOnPlanning(VirtualMachine* vm) {
}

} /* namespace alinous */
