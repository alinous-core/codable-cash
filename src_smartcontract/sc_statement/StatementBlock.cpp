/*
 * StatementBlock.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "sc_statement/StatementBlock.h"

namespace alinous {

StatementBlock::StatementBlock() : AbstractStatement(CodeElement::STMT_BLOCK) {
}

StatementBlock::~StatementBlock() {
	this->statements.deleteElements();
}

void StatementBlock::addStatement(AbstractStatement* stmt) noexcept {
	this->statements.addElement(stmt);
}

} /* namespace alinous */

int alinous::StatementBlock::binarySize() const {
}

void alinous::StatementBlock::toBinary(ByteBuffer* out) {
}

void alinous::StatementBlock::fromBinary(ByteBuffer* in) {
}
