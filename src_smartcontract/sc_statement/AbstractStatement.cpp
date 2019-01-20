/*
 * AbstractStatement.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "sc_statement/AbstractStatement.h"

namespace alinous {

AbstractStatement::AbstractStatement(short kind) : CodeElement(kind) {
}

AbstractStatement::~AbstractStatement() {
}

} /* namespace alinous */
