/*
 * ArgumentsListDeclare.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare/ArgumentsListDeclare.h"
#include "sc_declare/ArgumentDeclare.h"

namespace alinous {

ArgumentsListDeclare::ArgumentsListDeclare() : CodeElement(CodeElement::ARGUMENTS_LIST_DECLARE) {
}

ArgumentsListDeclare::~ArgumentsListDeclare() {
	this->list.deleteElements();
}

void ArgumentsListDeclare::addArgument(ArgumentDeclare* arg) noexcept {
	this->list.addElement(arg);
}

} /* namespace alinous */
