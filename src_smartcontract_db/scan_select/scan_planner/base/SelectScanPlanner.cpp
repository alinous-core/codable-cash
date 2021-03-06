/*
 * SelectScanPlanner.cpp
 *
 *  Created on: 2020/07/19
 *      Author: iizuka
 */

#include <cassert>

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolder.h"
#include "scan_select/scan_planner/base/TablesHolder.h"
#include "scan_select/scan_planner/base/ConditionsHolderStack.h"

#include "scan_select/scan_planner/analyze/AnalyzedScanPlan.h"

#include "scan_select/scan_condition/base/AbstractScanCondition.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_planner/scanner/factory/AbstractScannerFactory.h"

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

#include "trx/scan/transaction_scan_result/ScanResultExecutor.h"

#include "base/StackRelease.h"


namespace codablecash {

SelectScanPlanner::SelectScanPlanner() {
	this->conditions = new ConditionsHolder();
	this->tablesHolder = new TablesHolder();
	this->columnHolder = new ScanColumnHolder();
	this->plan = new AnalyzedScanPlan();
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
	this->conditions->analyzeConditions(vm, this);
}

void SelectScanPlanner::buildScannerFactories(VirtualMachine* vm) {
	this->tablesHolder->buildScannerFactories(vm, this);
}

void SelectScanPlanner::executeQuery(VirtualMachine* vm) {
	CodableDatabase* db = vm->getDb();

	AbstractScannerFactory* scanFactory = this->plan->getScanFactory();

	IJoinLeftSource* left = scanFactory->createScannerAsLeftSource(vm, this);

	ScanResultExecutor exec(left, db);
	exec.execScan();

	// TODO exec scan
}

ConditionsHolderStack* SelectScanPlanner::getConditionsStack() const noexcept {
	return this->conditions->getStack();
}


} /* namespace codablecash */
