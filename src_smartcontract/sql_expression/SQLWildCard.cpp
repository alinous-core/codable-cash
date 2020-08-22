/*
 * SQLWildCard.cpp
 *
 *  Created on: 2020/08/22
 *      Author: iizuka
 */

#include "sql_expression/SQLWildCard.h"

#include "sc_analyze/AnalyzedType.h"

#include "scan_planner/SelectScanPlanner.h"

#include "scan_columns/ScanColumnHolder.h"

#include "scan_columns/AllScanColumns.h"

#include "vm/VirtualMachine.h"
using codablecash::AllScanColumns;
using codablecash::ScanColumnHolder;
using codablecash::SelectScanPlanner;
namespace alinous {

SQLWildCard::SQLWildCard() : AbstractSQLExpression(CodeElement::SQL_EXP_WILDCARD) {

}

SQLWildCard::~SQLWildCard() {

}

int SQLWildCard::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void SQLWildCard::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_WILDCARD);
}

void SQLWildCard::fromBinary(ByteBuffer* in) {
}

void SQLWildCard::preAnalyze(AnalyzeContext* actx) {
}

void SQLWildCard::analyzeTypeRef(AnalyzeContext* actx) {
}

void SQLWildCard::analyze(AnalyzeContext* actx) {
}

AnalyzedType SQLWildCard::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void SQLWildCard::init(VirtualMachine* vm) {
}

AbstractVmInstance* SQLWildCard::interpret(VirtualMachine* vm) {
	return nullptr;
}

void SQLWildCard::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	AllScanColumns* col = new AllScanColumns();
	colHolder->push(col);
}

} /* namespace alinous */