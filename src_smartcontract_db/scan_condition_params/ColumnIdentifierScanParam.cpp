/*
 * ColumnIdentifierColumn.cpp
 *
 *  Created on: 2020/07/21
 *      Author: iizuka
 */

#include "scan_condition_params/ColumnIdentifierScanParam.h"

#include "base/UnicodeString.h"

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "sql_expression/SQLColumnIdentifier.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/SelectScanPlanner.h"

#include "engine/CodableDatabase.h"
#include "engine/CdbException.h"

#include "schema/SchemaManager.h"

#include "scan_planner_analyze/AnalyzedScanPlan.h"
#include "scan_planner_analyze/ScanTargetNameResolver.h"

#include "scan_table/AbstractScanTableTarget.h"


namespace codablecash {

ColumnIdentifierScanParam::ColumnIdentifierScanParam(const ColumnIdentifierScanParam& inst) : sqlColId(inst.sqlColId) {
	this->cdbColumn = inst.cdbColumn;
	this->str = nullptr;
	this->target = inst.target;
}

ColumnIdentifierScanParam::ColumnIdentifierScanParam(SQLColumnIdentifier* sqlColId) : sqlColId(sqlColId){
	this->cdbColumn = nullptr;
	this->str = nullptr;
	this->target = nullptr;
}

ColumnIdentifierScanParam::~ColumnIdentifierScanParam() {
	delete this->str;
	this->cdbColumn = nullptr;
}

const UnicodeString* ColumnIdentifierScanParam::toStringCode() noexcept {
	if(this->str == nullptr){
		delete this->str;
		this->str = new UnicodeString(L"");

		const UnicodeString* s = nullptr;
		s = this->sqlColId->getSchema();
		if(s != nullptr){
			this->str->append(s);
			this->str->append(L".");
		}
		s = this->sqlColId->getTableName();
		if(s != nullptr){
			this->str->append(s);
			this->str->append(L".");
		}

		s = this->sqlColId->getColumnName();
		this->str->append(s);
	}

	return this->str;
}


void ColumnIdentifierScanParam::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	CodableDatabase* db = vm->getDb();
	SchemaManager* scMgr = db->getSchemaManager();

	AnalyzedScanPlan* plan = planner->getPlan();
	ScanTargetNameResolver* aliasResolver = plan->getScanTargetNameResolver();

	UnicodeString tablefqn(L"");
	const UnicodeString* schemaName = this->sqlColId->getSchema();

	const UnicodeString* tableName = this->sqlColId->getTableName();
	const UnicodeString* colName = this->sqlColId->getColumnName();

	if(schemaName == nullptr && resolveAlias(tableName, aliasResolver)){
		return;
	}

	if(schemaName == nullptr){
		schemaName = &SchemaManager::PUBLIC;
	}

	CdbTable* table = scMgr->getTable(schemaName, tableName);
	this->cdbColumn = table->getColumn(colName);

	this->target = aliasResolver->get(table->getTableFqn());
}

IValueProvider* ColumnIdentifierScanParam::clone() const noexcept {
	return new ColumnIdentifierScanParam(*this);
}

bool ColumnIdentifierScanParam::isColumn() const noexcept {
	return true;
}

bool ColumnIdentifierScanParam::isFilterable(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) const noexcept {
	return detector->hasTarget(this->target);
}

bool ColumnIdentifierScanParam::resolveAlias(const UnicodeString* tableAlias, ScanTargetNameResolver* aliasResolver) {
	this->target = aliasResolver->get(tableAlias);
	if(this->target != nullptr){
		return true;
	}

	return false;
}

} /* namespace codablecash */
