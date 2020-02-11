/*
 * AbstractType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "sc_declare_types/AbstractType.h"

namespace alinous {

AbstractType::AbstractType(short kind) : CodeElement(kind) {
	this->dimension = 1;
}

AbstractType::~AbstractType() {

}

void AbstractType::addDimension() noexcept {
	this->dimension++;
}

int AbstractType::getDimension() const noexcept {
	return this->dimension;
}

} /* namespace alinous */
