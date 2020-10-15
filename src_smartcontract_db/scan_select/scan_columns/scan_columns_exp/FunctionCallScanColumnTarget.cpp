/*
 * FunctionCallScanColumn.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_select/scan_columns/scan_columns_exp/FunctionCallScanColumnTarget.h"

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

void FunctionCallScanColumnTarget::addArgument(AbstractScanColumnsTarget* arg) noexcept {
	this->arguments.addElement(arg);
}

const UnicodeString* FunctionCallScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->name);

		this->str->append(L"(");

		int maxLoop = this->arguments.size();
		for(int i = 0; i != maxLoop; ++i){
			if(i > 0){
				this->str->append(L", ");
			}

			AbstractScanColumnsTarget* value = this->arguments.get(i);
			this->str->append(value->toStringCode());
		}

		this->str->append(L")");
	}

	return this->str;
}

void FunctionCallScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* value = this->arguments.get(i);

		value->resolveColumns(vm, planner);
	}
}

} /* namespace codablecash */
