/*
 * AbstractVariableInstraction.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

AbstractVariableInstraction::AbstractVariableInstraction() {
	this->hasError = false;
}

AbstractVariableInstraction::~AbstractVariableInstraction() {

}

bool AbstractVariableInstraction::hasErrorOnAnalyze() const noexcept {
	return this->hasError;
}

} /* namespace alinous */
