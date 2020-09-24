/*
 * TableScanTarget.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_table/TableScanTarget.h"

#include "base/UnicodeString.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolder.h"

#include "vm/VirtualMachine.h"

#include "schema/SchemaManager.h"
#include "schema/Schema.h"

#include "table/CdbTable.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "scan_planner_analyze/ScanTargetNameResolver.h"
#include "scan_planner_analyze/AnalyzedScanPlan.h"

#include "scan_planner_scanner_ctx/FilterConditionDitector.h"

#include "scan_planner_scanner_ctx_index/TableIndexDetector.h"

namespace codablecash {

TableScanTarget::TableScanTarget() {
	this->schema = nullptr;
	this->tableName = nullptr;
	this->alias = nullptr;

	this->str = nullptr;

	this->table = nullptr;
}

TableScanTarget::~TableScanTarget() {
	delete this->schema;
	delete this->tableName;
	delete this->alias;

	delete this->str;
}

void TableScanTarget::setSchema(const UnicodeString* schema) noexcept {
	if(schema != nullptr){
		this->schema = new UnicodeString(schema);
	}
}

void TableScanTarget::setTableName(const UnicodeString* tableName) noexcept {
	if(tableName != nullptr){
		this->tableName = new UnicodeString(tableName);
	}
}

void TableScanTarget::setAlias(const UnicodeString* alias)noexcept {
	if(alias != nullptr){
		this->alias = new UnicodeString(alias);
	}
}

const UnicodeString* TableScanTarget::toString() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		if(this->schema != nullptr){
			this->str->append(this->schema);
			this->str->append(L".");
		}

		this->str->append(this->tableName);

		if(this->alias != nullptr){
			this->str->append(L" AS ");
			this->str->append(this->alias);
		}
	}
	return this->str;
}

void TableScanTarget::resolveTable(VirtualMachine* vm, SelectScanPlanner* planner) {
	AnalyzedScanPlan* plan = planner->getPlan();

	CodableDatabase* db = vm->getDb();
	SchemaManager* schemaManager = db->getSchemaManager();

	const UnicodeString* scName = this->schema != nullptr ? this->schema : vm->getCurrentSchema();
	this->table = schemaManager->getTable(scName, this->tableName);


	ScanTargetNameResolver* resolver = plan->getScanTargetNameResolver();

	UnicodeString tableFqn(scName);
	tableFqn.append(L".");
	tableFqn.append(this->tableName);

	resolver->add(&tableFqn, this);

	if(this->alias != nullptr){
		resolver->add(this->alias, this);
	}

	this->metadata = this->table->getMetadata();
}

void TableScanTarget::collectScanTargets(VirtualMachine* vm, SelectScanPlanner* planner, ArrayList<AbstractScanTableTarget>* list) {
	list->addElement(this);
}

AbstractScannerFactory* TableScanTarget::getScanFactory(VirtualMachine* vm, SelectScanPlanner* planner) {
	ConditionsHolder* holder = planner->getConditions();

	RootScanCondition* root = holder->getRoot();

	FilterConditionDitector filterDetector(vm, planner);
	filterDetector.detect(this);

	TableIndexDetector indexDetextor(vm, planner);
	indexDetextor.detect(filterDetector.getCondition());

	// FIXME getScanFactory
	return nullptr;
}

bool TableScanTarget::hasTarget(const AbstractScanTableTarget* target) const noexcept {
	return target == this;
}

} /* namespace codablecash */
