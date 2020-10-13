/*
 * AbstractSQLPart.cpp
 *
 *  Created on: 2019/02/21
 *      Author: iizuka
 */

#include "lang_sql/sql/AbstractSQLPart.h"

namespace alinous {

AbstractSQLPart::AbstractSQLPart(int kind) : CodeElement(kind) {
}

AbstractSQLPart::~AbstractSQLPart() {
}

bool AbstractSQLPart::isExecutable() {
	return true;
}

} /* namespace alinous */
