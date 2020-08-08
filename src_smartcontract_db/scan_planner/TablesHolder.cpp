/*
 * TablesHolder.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_planner/TablesHolder.h"

#include "scan_table/AbstractScanTableTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

TablesHolder::TablesHolder() {
	this->str = nullptr;
}

TablesHolder::~TablesHolder() {
	this->list.deleteElements();
	this->stack.deleteElements();
	delete this->str;
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

const UnicodeString* TablesHolder::toString() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanTableTarget* target = this->list.get(i);

			if(i > 0){
				this->str->append(L", ");
			}
			this->str->append(target->toString());
		}
	}

	return this->str;
}

} /* namespace codablecash */
