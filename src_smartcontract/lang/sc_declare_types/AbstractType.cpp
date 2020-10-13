/*
 * AbstractType.cpp
 *
 *  Created on: 2019/01/19
 *      Author: iizuka
 */

#include "lang/sc_declare_types/AbstractType.h"


namespace alinous {

AbstractType::AbstractType(short kind) : CodeElement(kind) {
	this->dimension = 0;
}

AbstractType::~AbstractType() {

}

void AbstractType::addDimension() noexcept {
	this->dimension++;
}

int AbstractType::getDimension() const noexcept {
	return this->dimension;
}

int AbstractType::binarySize() const {
	return 1;
}

void AbstractType::toBinary(ByteBuffer* out) {
	out->put(this->dimension);
}

void AbstractType::fromBinary(ByteBuffer* in) {
	this->dimension = in->get();
}

} /* namespace alinous */
