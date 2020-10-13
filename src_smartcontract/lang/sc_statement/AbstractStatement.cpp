/*
 * AbstractStatement.cpp
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#include "lang/sc_statement/AbstractStatement.h"

namespace alinous {

AbstractStatement::AbstractStatement(short kind) : CodeElement(kind) {
}

AbstractStatement::~AbstractStatement() {
}

bool AbstractStatement::isExecutable() {
	return true;
}

bool AbstractStatement::hasConstructor() const noexcept {
	return false;
}


} /* namespace alinous */
