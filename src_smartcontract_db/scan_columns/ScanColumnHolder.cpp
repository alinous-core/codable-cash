/*
 * ScanColumnHolder.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/ScanColumnHolder.h"
#include "scan_columns/AbstractScanColumnsTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

ScanColumnHolder::ScanColumnHolder() {

}

ScanColumnHolder::~ScanColumnHolder() {
	this->stack.deleteElements();
	this->list.deleteElements();
}

void ScanColumnHolder::push(AbstractScanColumnsTarget* column) noexcept {
	this->stack.addElement(column);
}

AbstractScanColumnsTarget* ScanColumnHolder::pop() noexcept {
	int index = this->stack.size() - 1;

	return this->stack.remove(index);
}

void ScanColumnHolder::addColumn(AbstractScanColumnsTarget* col) noexcept {
	this->list.addElement(col);
}

void ScanColumnHolder::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* col = this->list.get(i);

		// FIXME
	}
}


UnicodeString* ScanColumnHolder::toCodeString() noexcept {
	UnicodeString* str = new UnicodeString(L"");

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* col = this->list.get(i);

		if(i != 0){
			str->append(L", ");
		}

		str->append(col->toStringCode());
	}

	return str;
}

} /* namespace codablecash */
