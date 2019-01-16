/*
 * CodeElement.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc/CodeElement.h"
#include "alinous_lang/Token.h"

namespace alinous {

CodeElement::CodeElement(short kind) {
	this->kind = kind;
	this->beginLine = 0;
	this->beginColumn = 0;
	this->endLine = 0;
	this->endColumn = 0;
}

CodeElement::~CodeElement() {
}

void CodeElement::setPositions(int beginLine, int beginColumn, int endLine, int endColumn) {
	this->beginLine = beginLine;
	this->beginColumn = beginColumn;
	this->endLine = endLine;
	this->endColumn = endColumn;
}

void CodeElement::setPositions(Token* token, CodeElement* end) {
	this->beginLine = token->beginLine;
	this->beginColumn = token->beginColumn;
	this->endLine = end->endLine;
	this->endColumn = end->endColumn;
}

void CodeElement::setPosition(CodeElement* element) {
	if(this->beginLine == 0 && this->beginColumn == 0){
		this->beginLine = element->beginLine;
		this->beginColumn = element->beginColumn;
		return;
	}

	this->endLine = element->endLine;
	this->endColumn = element->endColumn;
}

void CodeElement::setPosition(Token* token) {
	if(this->beginLine == 0 && this->beginColumn == 0){
		this->beginLine = token->beginLine;
		this->beginColumn = token->beginColumn;
		return;
	}

	this->endLine = token->endLine;
	this->endColumn = token->endColumn;
}

} /* namespace alinous */
