/*
 * FunctionCallScanColumn.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_exp/FunctionCallScanColumnTarget.h"

#include "base/UnicodeString.h"


namespace codablecash {

FunctionCallScanColumnTarget::FunctionCallScanColumnTarget() {
	this->name = nullptr;
}

FunctionCallScanColumnTarget::~FunctionCallScanColumnTarget() {
	delete this->name;
	this->arguments.deleteElements();
}

void FunctionCallScanColumnTarget::setName(const UnicodeString* name) noexcept {
	this->name = new UnicodeString(name);
}

void FunctionCallScanColumnTarget::addArgument(AbstractScanColumns* arg) noexcept {
	this->arguments.addElement(arg);
}

} /* namespace codablecash */
