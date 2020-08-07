/*
 * TablesHolder.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_planner/TablesHolder.h"

#include "scan_table/AbstractScanTableTarget.h"

namespace codablecash {

TablesHolder::TablesHolder() {

}

TablesHolder::~TablesHolder() {
	this->list.deleteElements();

}

void TablesHolder::addScanTarget(AbstractScanTableTarget* target) noexcept {
	this->list.addElement(target);
}

void TablesHolder::push(AbstractScanTableTarget* target) noexcept {
	this->stack.addElement(target);
}

AbstractScanTableTarget* TablesHolder::pop() noexcept {
	int idx = this->stack.size() - 1;
	return this->stack.get(idx);
}

bool TablesHolder::isEmpty() const noexcept {
	return this->stack.isEmpty();
}

} /* namespace codablecash */
