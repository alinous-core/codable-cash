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

#include "scan_planner_analyze/AnalyzedScanPlan.h"

#include "scan_condition/AbstractScanCondition.h"

#include "scan_columns/ScanColumnHolder.h"

#include "vm/VirtualMachine.h"

namespace codablecash {

SelectScanPlanner::SelectScanPlanner() {
	this->conditions = new ConditionsHolder();
	this->tablesHolder = new TablesHolder();
	this->columnHolder = new ScanColumnHolder();
	this->plan = nullptr;
}

SelectScanPlanner::~SelectScanPlanner() {
	delete this->conditions;
	delete this->tablesHolder;
	delete this->columnHolder;
	delete this->plan;
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

void SelectScanPlanner::makeplan(VirtualMachine* vm) {
	delete this->plan;
	this->plan = new AnalyzedScanPlan();

	resolveTable(vm);
	resolveColumn(vm);

	analyzeConditions(vm);

	buildScannerFactories(vm);
}

void SelectScanPlanner::resolveTable(VirtualMachine* vm) {
	this->tablesHolder->resolveTable(vm, this);
}

void SelectScanPlanner::resolveColumn(VirtualMachine* vm) {
	this->columnHolder->resolveColumns(vm, this);
}

void SelectScanPlanner::analyzeConditions(VirtualMachine* vm) {
}

void SelectScanPlanner::buildScannerFactories(VirtualMachine* vm) {
	this->tablesHolder->buildScannerFactories(vm, this);
}

void SelectScanPlanner::executeQuery(VirtualMachine* vm) {
}

} /* namespace codablecash */
