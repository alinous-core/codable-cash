/*
 * JsonKeyValuePair.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "sc_expression_json/JsonKeyValuePairExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

JsonKeyValuePairExpression::JsonKeyValuePairExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_VALUE_PAIR) {

}

JsonKeyValuePairExpression::~JsonKeyValuePairExpression() {

}

void JsonKeyValuePairExpression::preAnalyze(AnalyzeContext* actx) {
}

void JsonKeyValuePairExpression::analyzeTypeRef(AnalyzeContext* actx) {
}

void JsonKeyValuePairExpression::analyze(AnalyzeContext* actx) {
}

AnalyzedType JsonKeyValuePairExpression::getType(AnalyzeContext* actx) {
}

void JsonKeyValuePairExpression::init(VirtualMachine* vm) {
}

AbstractVmInstance* JsonKeyValuePairExpression::interpret(VirtualMachine* vm) {
}

int JsonKeyValuePairExpression::binarySize() const {
}

void JsonKeyValuePairExpression::toBinary(ByteBuffer* out) {
}

void JsonKeyValuePairExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
