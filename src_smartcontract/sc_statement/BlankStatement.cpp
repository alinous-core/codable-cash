/*
 * BlankStatement.cpp
 *
 *  Created on: 2019/02/15
 *      Author: iizuka
 */

#include "sc_statement/BlankStatement.h"

namespace alinous {

BlankStatement::BlankStatement() : AbstractStatement(CodeElement::STMT_BLANK) {
}

BlankStatement::~BlankStatement() {
}

} /* namespace alinous */
