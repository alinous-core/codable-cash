/*
 * SelectScanPlanner.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include <cassert>

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolder.h"
#include "scan_planner/TablesHolder.h"

#include "scan_condition/AbstractScanCondition.h"

#include "scan_columns/ScanColumnHolder.h"

#include "vm/VirtualMachine.h"

namespace codablecash {

SelectScanPlanner::SelectScanPlanner() {
	this->conditions = new ConditionsHolder();
	this->tablesHolder = new TablesHolder();
	this->columnHolder = new ScanColumnHolder();
}

SelectScanPlanner::~SelectScanPlanner() {
	delete this->conditions;
	delete this->tablesHolder;
	delete this->columnHolder;
}

void SelectScanPlanner::push(AbstractScanConditionElement* cond) noexcept {
	this->conditions->push(cond);
}

AbstractScanConditionElement* SelectScanPlanner::top() const noexcept {
	return this->conditions->top();
}

AbstractScanConditionElement* SelectScanPlanner::pop() noexcept{
	return this->conditions->pop();
}

void SelectScanPlanner::plan(VirtualMachine* vm) {
	resolveTable(vm);
	resolveColumn(vm);

	analyzeConditions(vm);

	buildScannerFactories(vm);
}

void SelectScanPlanner::resolveTable(VirtualMachine* vm) {
	this->tablesHolder->resolveTable(vm, this);
}

void SelectScanPlanner::resolveColumn(VirtualMachine* vm) {

}

void SelectScanPlanner::analyzeConditions(VirtualMachine* vm) {
}

void SelectScanPlanner::buildScannerFactories(VirtualMachine* vm) {
}

void SelectScanPlanner::executeQuery(VirtualMachine* vm) {
}

} /* namespace codablecash */
