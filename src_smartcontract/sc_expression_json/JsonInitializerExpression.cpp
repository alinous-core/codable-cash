/*
 * JsonInitializer.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "sc_expression_json/JsonInitializerExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

JsonInitializerExpression::JsonInitializerExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_INITIALIZER) {

}

JsonInitializerExpression::~JsonInitializerExpression() {

}

void JsonInitializerExpression::preAnalyze(AnalyzeContext* actx) {
}

void JsonInitializerExpression::analyzeTypeRef(AnalyzeContext* actx) {
}

void JsonInitializerExpression::analyze(AnalyzeContext* actx) {
}

AnalyzedType JsonInitializerExpression::getType(AnalyzeContext* actx) {
}

void JsonInitializerExpression::init(VirtualMachine* vm) {
}

AbstractVmInstance* JsonInitializerExpression::interpret(VirtualMachine* vm) {
}

int JsonInitializerExpression::binarySize() const {
}

void JsonInitializerExpression::toBinary(ByteBuffer* out) {
}

void JsonInitializerExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
