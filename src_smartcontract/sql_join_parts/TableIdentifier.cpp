/*
 * TableIdentifier.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_join_parts/TableIdentifier.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/TablesHolder.h"

#include "scan_table/TableScanTarget.h"


namespace alinous {

TableIdentifier::TableIdentifier() : AbstractJoinPart(CodeElement::SQL_EXP_TABLE_ID) {
	this->schema = nullptr;
	this->tableName =nullptr;
	this->alias = nullptr;
}

TableIdentifier::~TableIdentifier() {
	delete this->schema;
	delete this->tableName;
	delete this->alias;
}

void TableIdentifier::setSchema(UnicodeString* schema) noexcept {
	this->schema = schema;
}

void TableIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

void TableIdentifier::setAlias(UnicodeString* alias) noexcept {
	this->alias = alias;
}

int TableIdentifier::binarySize() const {
	checkNotNull(this->tableName);

	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	if(this->schema != nullptr){
		total += stringSize(this->schema);
	}

	total += stringSize(this->tableName);

	total += sizeof(uint8_t);
	if(this->alias != nullptr){
		total += stringSize(this->alias);
	}

	return total;
}

void TableIdentifier::toBinary(ByteBuffer* out) {
	checkNotNull(this->tableName);

	out->putShort(CodeElement::SQL_EXP_TABLE_ID);

	out->put(this->schema != nullptr ? 1 : 0);
	if(this->schema != nullptr){
		putString(out, this->schema);
	}
	putString(out, this->tableName);

	out->put(this->alias != nullptr ? 1 : 0);
	if(this->alias != nullptr){
		putString(out, this->alias);
	}
}

void TableIdentifier::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		this->schema = getString(in);
	}

	this->tableName = getString(in);

	bl = in->get();
	if(bl == 1){
		this->alias = getString(in);
	}
}

void TableIdentifier::preAnalyze(AnalyzeContext* actx) {
}

void TableIdentifier::analyzeTypeRef(AnalyzeContext* actx) {
}

void TableIdentifier::analyze(AnalyzeContext* actx) {
}

AnalyzedType TableIdentifier::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void TableIdentifier::init(VirtualMachine* vm) {
}

AbstractVmInstance* TableIdentifier::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	TablesHolder* tables = planner->getTablesHolder();

	TableScanTarget* target = new TableScanTarget();

	tables->push(target);

	return nullptr;
}


} /* namespace alinous */
