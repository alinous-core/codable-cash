/*
 * SQLColumnIdentifier.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLColumnIdentifier.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionsHolderStackMarker.h"

#include "scan_condition_params/ColumnIdentifierScanParam.h"

#include "vm/VirtualMachine.h"

#include "scan_columns/ScanColumnHolder.h"
#include "scan_columns/ScanColumn.h"


namespace alinous {

SQLColumnIdentifier::SQLColumnIdentifier() : AbstractSQLExpression(CodeElement::SQL_EXP_COLUMN_ID){
	this->schema = nullptr;
	this->tableName =nullptr;
	this->columnName =nullptr;
}

SQLColumnIdentifier::~SQLColumnIdentifier() {
	delete this->schema;
	delete this->tableName;
	delete this->columnName;
}

void SQLColumnIdentifier::setSchema(UnicodeString* schema) noexcept {
	this->schema = schema;
}

void SQLColumnIdentifier::setTableName(UnicodeString* tableName) noexcept {
	this->tableName = tableName;
}

void SQLColumnIdentifier::setColumnName(UnicodeString* columnName) noexcept {
	this->columnName = columnName;
}

int SQLColumnIdentifier::binarySize() const {
	checkNotNull(this->columnName);

	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);
	if(this->schema != nullptr){
		total += stringSize(this->schema);
	}

	total += sizeof(uint8_t);
	if(this->tableName != nullptr){
		total += stringSize(this->tableName);
	}

	total += stringSize(this->columnName);

	return total;
}

void SQLColumnIdentifier::toBinary(ByteBuffer* out) {
	checkNotNull(this->columnName);

	out->putShort(CodeElement::SQL_EXP_COLUMN_ID);

	out->put(this->schema != nullptr ? 1 : 0);
	if(this->schema != nullptr){
		putString(out, this->schema);
	}

	out->put(this->tableName != nullptr ? 1 : 0);
	if(this->tableName != nullptr){
		putString(out, this->tableName);
	}

	putString(out, this->columnName);
}

void SQLColumnIdentifier::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	if(bl == 1){
		this->schema = getString(in);
	}
	bl = in->get();
	if(bl == 1){
		this->tableName = getString(in);
	}
	this->columnName = getString(in);
}

void SQLColumnIdentifier::preAnalyze(AnalyzeContext* actx) {
}

void SQLColumnIdentifier::analyzeTypeRef(AnalyzeContext* actx) {
}

void SQLColumnIdentifier::analyze(AnalyzeContext* actx) {
}

AnalyzedType SQLColumnIdentifier::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void SQLColumnIdentifier::init(VirtualMachine* vm) {
}

AbstractVmInstance* SQLColumnIdentifier::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	ColumnIdentifierScanParam* param = new ColumnIdentifierScanParam(this);
	planner->push(param);

	return nullptr;
}

void SQLColumnIdentifier::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	ScanColumn* col = new ScanColumn(this);
	colHolder->push(col);
}

} /* namespace alinous */
