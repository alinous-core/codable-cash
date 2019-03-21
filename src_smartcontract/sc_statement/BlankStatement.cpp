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

int BlankStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void BlankStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::STMT_BLANK);
}

void BlankStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
