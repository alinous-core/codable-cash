/*
 * ScanColumnHolder.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/ScanColumnHolder.h"
#include "scan_columns/AbstractScanColumnsTarget.h"

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

} /* namespace codablecash */
