/*
 * AbstractSQLExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql/AbstractSQLExpression.h"

namespace alinous {

AbstractSQLExpression::AbstractSQLExpression(int kind) : CodeElement(kind) {
}

AbstractSQLExpression::~AbstractSQLExpression() {
}

} /* namespace alinous */
