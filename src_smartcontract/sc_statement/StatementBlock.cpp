/*
 * StatementBlock.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "sc_statement/StatementBlock.h"

#include "sc_declare/MethodDeclare.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze_stack/AnalyzeStackManager.h"
#include "sc_analyze_stack/AnalyzeStackPopper.h"

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

void StatementBlock::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->analyzeTypeRef(actx);
	}
}

void StatementBlock::analyze(AnalyzeContext* actx) {
	short parentKind = this->parent->getKind();
	if(parentKind == CodeElement::METHOD_DECLARE){
		analyzeMethodDeclareBlock(actx);
		return;
	}

	int maxLoop = this->statements.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractStatement* stmt = this->statements.get(i);
		stmt->analyze(actx);
	}
}

void StatementBlock::analyzeMethodDeclareBlock(AnalyzeContext* actx) {
	MethodDeclare* method = dynamic_cast<MethodDeclare*>(this->parent);

	AnalyzeStackManager* stack = actx->getAnalyzeStackManager();
	AnalyzeStackPopper popper(stack, true);

	stack->addFunctionStack();

	// FIXME analyzeMethodDeclareBlock

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
