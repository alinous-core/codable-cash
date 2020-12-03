/*
 * AbstractColumnsIndexWrapper.cpp
 *
 *  Created on: 2020/11/26
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

namespace codablecash {

AbstractColumnsIndexWrapper::AbstractColumnsIndexWrapper() {
	this->column = nullptr;
	this->target = nullptr;
	this->index = nullptr;
}

AbstractColumnsIndexWrapper::~AbstractColumnsIndexWrapper() {
	this->column = nullptr;
	this->target = nullptr;
	this->index = nullptr;
}

} /* namespace codablecash */
