/*
 * AbstractSQLPart.cpp
 *
 *  Created on: 2019/02/21
 *      Author: iizuka
 */

#include "sql/AbstractSQLPart.h"

namespace alinous {

AbstractSQLPart::AbstractSQLPart(int kind) : CodeElement(kind) {
}

AbstractSQLPart::~AbstractSQLPart() {
}

} /* namespace alinous */
