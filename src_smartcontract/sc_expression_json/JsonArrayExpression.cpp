/*
 * JsonArrayExpression.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "sc_expression_json/JsonArrayExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"


namespace alinous {

JsonArrayExpression::JsonArrayExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_ARRAY) {

}

JsonArrayExpression::~JsonArrayExpression() {

}

void JsonArrayExpression::preAnalyze(AnalyzeContext* actx) {
}

void JsonArrayExpression::analyzeTypeRef(AnalyzeContext* actx) {
}

void JsonArrayExpression::analyze(AnalyzeContext* actx) {
}

AnalyzedType JsonArrayExpression::getType(AnalyzeContext* actx) {
}

void JsonArrayExpression::init(VirtualMachine* vm) {
}

AbstractVmInstance* JsonArrayExpression::interpret(VirtualMachine* vm) {
}

int JsonArrayExpression::binarySize() const {
}

void JsonArrayExpression::toBinary(ByteBuffer* out) {
}

void JsonArrayExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
