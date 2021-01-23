/*
 * AbstractColumnsIndexWrapper.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

#include "base/UnicodeString.h"

namespace codablecash {

AbstractColumnsIndexWrapper::AbstractColumnsIndexWrapper(
		const AbstractColumnsIndexWrapper& inst) {
	this->target = inst.target;
	this->index = inst.index;
	this->str = nullptr;
}


AbstractColumnsIndexWrapper::AbstractColumnsIndexWrapper() {
	this->target = nullptr;
	this->index = nullptr;
	this->str = nullptr;
}

AbstractColumnsIndexWrapper::~AbstractColumnsIndexWrapper() {
	this->target = nullptr;
	this->index = nullptr;

	resetStr();
}

void AbstractColumnsIndexWrapper::resetStr() noexcept {
	delete this->str;
	this->str = nullptr;
}

} /* namespace codablecash */
