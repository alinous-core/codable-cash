/*
 * AbstractVariableInstraction.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "vm/variable_access/AbstractVariableInstraction.h"

namespace alinous {

AbstractVariableInstraction::AbstractVariableInstraction(uint8_t type) {
	this->type = type;
	this->hasError = false;
}

AbstractVariableInstraction::~AbstractVariableInstraction() {

}

bool AbstractVariableInstraction::hasErrorOnAnalyze() const noexcept {
	return this->hasError;
}

uint8_t AbstractVariableInstraction::getType() const noexcept {
	return this->type;
}


} /* namespace alinous */
