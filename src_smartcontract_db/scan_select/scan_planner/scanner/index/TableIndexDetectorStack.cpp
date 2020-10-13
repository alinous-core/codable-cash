/*
 * TableIndexDetectorStack.cpp
 *
 *  Created on: 2020/09/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/scanner/index/TableIndexDetectorStack.h"

#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

namespace codablecash {

TableIndexDetectorStack::TableIndexDetectorStack() : markStack(4) {

}

TableIndexDetectorStack::~TableIndexDetectorStack() {
	this->stack.deleteElements();
}

bool TableIndexDetectorStack::isEmpty() const noexcept {
	if(this->markStack.size() == 0){
		return this->stack.isEmpty();
	}

	int topidx = this->markStack.size() - 1;
	int index = this->markStack.get(topidx);

	return this->stack.size() == index;
}

void TableIndexDetectorStack::push(AbstractIndexCandidate* candidate) noexcept {
	this->stack.addElement(candidate);
}

AbstractIndexCandidate* TableIndexDetectorStack::pop() noexcept {
	int index = this->stack.size() - 1;
	return this->stack.remove(index);
}

void TableIndexDetectorStack::mark() noexcept {
	int index = this->stack.size();
	this->markStack.addElement(index);
}

void TableIndexDetectorStack::unmark() noexcept {
	int index = this->markStack.size() - 1;
	this->markStack.remove(index);
}

} /* namespace codablecash */
