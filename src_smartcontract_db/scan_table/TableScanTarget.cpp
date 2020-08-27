/*
 * TableScanTarget.cpp
 *
 *  Created on: 2020/08/07
 *      Author: iizuka
 */

#include "scan_table/TableScanTarget.h"

#include "base/UnicodeString.h"

#include "scan_planner/SelectScanPlanner.h"

namespace codablecash {

TableScanTarget::TableScanTarget() {
	this->schema = nullptr;
	this->tableName = nullptr;
	this->alias = nullptr;

	this->str = nullptr;
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

void TableScanTarget::resolveTable(VirtualMachine* vm,	SelectScanPlanner* planner) {
	AnalyzedScanPlan* plan = planner->getPlan();


	// FIXME resolveTable
}

} /* namespace codablecash */
