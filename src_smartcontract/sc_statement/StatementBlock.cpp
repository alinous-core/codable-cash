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

void StatementBlock::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->setParent(this);
		stmt->preAnalyze(actx);
	}
}

void StatementBlock::analyze(AnalyzeContext* actx) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->analyze(actx);
	}
}

void StatementBlock::addStatement(AbstractStatement* stmt) noexcept {
	this->statements.addElement(stmt);
}

int StatementBlock::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		total += stmt->binarySize();
	}

	return total;
}

void StatementBlock::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::STMT_BLOCK);

	int maxLoop = this->statements.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->toBinary(out);
	}
}

void StatementBlock::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsStatement(element);

		AbstractStatement* stmt = dynamic_cast<AbstractStatement*>(element);
		this->statements.addElement(stmt);
	}
}

void StatementBlock::interpret(VirtualMachine* vm) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->interpret(vm);
	}
}

} /* namespace alinous */
