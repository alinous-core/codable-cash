/*
 * SQLWildCard.cpp
 *
 *  Created on: 2020/08/22
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLWildCard.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"
#include "scan_select/scan_columns/AllScanColumns.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_condition/params/WildCardScanParam.h"

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
	if(vm->isSelectPlanning()){
		SelectScanPlanner* planner = vm->getSelectPlanner();
		ConditionsHolderStackMarker marker(planner->getConditionsStack());

		WildCardScanParam* param = new WildCardScanParam();
		planner->push(param);
	}

	return nullptr;
}

void SQLWildCard::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	AllScanColumns* col = new AllScanColumns();
	colHolder->push(col);
}

} /* namespace alinous */
