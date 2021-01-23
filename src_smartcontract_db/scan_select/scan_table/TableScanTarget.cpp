/*
 * TableScanTarget.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_select/scan_table/TableScanTarget.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolder.h"

#include "vm/VirtualMachine.h"

#include "schema_table/schema/SchemaManager.h"
#include "schema_table/schema/Schema.h"

#include "schema_table/table/CdbTable.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "scan_select/scan_planner/analyze/ScanTargetNameResolver.h"
#include "scan_select/scan_planner/analyze/AnalyzedScanPlan.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"

#include "scan_select/scan_planner/scanner/index/TableIndexDetector.h"
#include "scan_select/scan_planner/scanner/index/AbstractIndexCandidate.h"

#include "scan_select/scan_planner/scanner/factory/TableScannerFactory.h"

#include "base/StackRelease.h"

#include "scan_select/scan_planner/scanner/index_resolv/IndexResolver.h"
#include "scan_select/scan_planner/scanner/index_resolv/AbstractColumnsIndexWrapper.h"

namespace codablecash {

TableScanTarget::TableScanTarget() {
	this->schema = nullptr;
	this->tableName = nullptr;
	this->alias = nullptr;

	this->str = nullptr;

	this->table = nullptr;
}

codablecash::TableScanTarget::TableScanTarget(const wchar_t* schema, const wchar_t* table) {
	this->schema = new UnicodeString(schema);
	this->tableName = new UnicodeString(table);
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

	this->metadata = this->table->getMetadata(this);
}

void TableScanTarget::collectScanTargets(VirtualMachine* vm, SelectScanPlanner* planner, ArrayList<AbstractScanTableTarget>* list) {
	list->addElement(this);
}

AbstractScannerFactory* TableScanTarget::getScanFactory(VirtualMachine* vm, SelectScanPlanner* planner) {
	ConditionsHolder* holder = planner->getConditions();

	RootScanCondition* root = holder->getRoot();

	FilterConditionDitector filterDetector(vm, planner);
	filterDetector.detect(this);

	AbstractScanCondition* filterCondition = filterDetector.getCondition();

	TableIndexDetector indexDetextor(vm, planner, this);
	indexDetextor.detect(filterCondition);

	AbstractIndexCandidate* indexCandidate = nullptr;
	if(!indexDetextor.isEmpty()){
		indexCandidate = indexDetextor.pop();
	}
	__STP(indexCandidate);


	AbstractColumnsIndexWrapper* indexWrapper = nullptr;
	{
		IndexResolver resolver(vm->getDb());
		if(indexCandidate != nullptr){
			resolver.analyze(indexCandidate);

			indexWrapper = resolver.getResult();
			indexWrapper = indexWrapper != nullptr ? indexWrapper->clone() : nullptr;
		}
	}

	TableScannerFactory* factory = new TableScannerFactory(this, this->table, this->metadata, indexWrapper);
	factory->setFilterCondition(filterCondition);

	return factory;
}

bool TableScanTarget::hasTarget(const AbstractScanTableTarget* target) const noexcept {
	return target == this;
}

ScanTableColumnParam* TableScanTarget::findTableColumns(const UnicodeString* colName) const {
	CdbTableColumn* column = this->table->getColumn(colName);
	if(column != nullptr){
		ScanTableColumnParam* param = new ScanTableColumnParam();
		param->table = this->table;
		param->column = column;
		param->target = this;

		return param;
	}

	return nullptr;
}

} /* namespace codablecash */
