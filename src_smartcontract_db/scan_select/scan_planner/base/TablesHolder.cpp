/*
 * TablesHolder.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_select/scan_planner/base/TablesHolder.h"

#include "scan_select/scan_table/AbstractScanTableTarget.h"
#include "scan_select/scan_table/CrossJoinScanTarget.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

#include "scan_select/scan_planner/analyze/AnalyzedScanPlan.h"


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
	return this->stack.remove(idx);
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

void TablesHolder::resolveTable(VirtualMachine* vm,	SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanTableTarget* target = this->list.get(i);

		target->resolveTable(vm, planner);
	}
}

void TablesHolder::buildScannerFactories(VirtualMachine* vm, SelectScanPlanner* planner) {
	AbstractScannerFactory* factory = buildScanFactory(vm, planner);

	AnalyzedScanPlan* plan = planner->getPlan();
	plan->setScanFactory(factory);

}

AbstractScannerFactory* TablesHolder::buildScanFactory(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	if(maxLoop == 1){
		AbstractScanTableTarget* target = this->list.get(0);

		AbstractScannerFactory* factory = target->getScanFactory(vm, planner);
		return factory;
	}

	// SELECT * FROM table1, table2, table3
	AbstractScanTableTarget* target = buildOuterJoinTarget();
	AbstractScannerFactory* factory = target->getScanFactory(vm, planner);

	return factory;
}

AbstractScanTableTarget* TablesHolder::buildOuterJoinTarget() {
	AbstractScanTableTarget* target = this->list.get(0);

	int maxLoop = this->list.size();
	for(int i = 1; i != maxLoop; ++i){
		AbstractScanTableTarget* targetRight = this->list.get(i);

		CrossJoinScanTarget* crossJoin = new CrossJoinScanTarget();
		crossJoin->setLeft(target);
		crossJoin->setRight(targetRight);

		target = crossJoin;
	}

	return target;
}

} /* namespace codablecash */
