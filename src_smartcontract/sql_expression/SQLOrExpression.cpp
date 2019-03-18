/*
 * SQLOrExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLOrExpression.h"

namespace alinous {

SQLOrExpression::SQLOrExpression() : AbstractSQLBinaryExpression(CodeElement::SQL_EXP_OR) {
}

SQLOrExpression::~SQLOrExpression() {
}

} /* namespace alinous */

int alinous::SQLOrExpression::binarySize() const {
}

void alinous::SQLOrExpression::toBinary(ByteBuffer* out) {
}

void alinous::SQLOrExpression::fromBinary(ByteBuffer* in) {
}
