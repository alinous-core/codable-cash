/*
 * ScanColumnHolder.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/ScanColumnHolder.h"
#include "scan_columns/AbstractScanColumns.h"

namespace codablecash {

ScanColumnHolder::ScanColumnHolder() {

}

ScanColumnHolder::~ScanColumnHolder() {

}

void ScanColumnHolder::push(AbstractScanColumns* column) noexcept {
	this->stack.addElement(column);
}

/*AbstractScanColumns* ScanColumnHolder::top() const noexcept {
	int index = this->stack.size() - 1;
	return this->stack.get(index);
}*/

AbstractScanColumns* ScanColumnHolder::pop() noexcept {
	int index = this->stack.size() - 1;

	return this->stack.remove(index);
}

} /* namespace codablecash */
