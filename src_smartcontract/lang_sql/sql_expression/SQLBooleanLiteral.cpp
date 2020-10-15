/*
 * SQLBooleanLiteral.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLBooleanLiteral.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/params/BooleanScanParam.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_params/BooleanLiteralColumnParam.h"


namespace alinous {

SQLBooleanLiteral::SQLBooleanLiteral() : AbstractSQLExpression(CodeElement::SQL_EXP_BOOL_LITERAL) {
	this->value = false;
}

SQLBooleanLiteral::~SQLBooleanLiteral() {
}

void SQLBooleanLiteral::setValue(bool value) noexcept {
	this->value = value;
}

int SQLBooleanLiteral::binarySize() const {
	int total = sizeof(uint16_t);
	total += sizeof(uint8_t);

	return total;
}

void SQLBooleanLiteral::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_BOOL_LITERAL);
	out->put(this->value ? 1 : 0);
}

void SQLBooleanLiteral::fromBinary(ByteBuffer* in) {
	uint8_t bl = in->get();
	this->value = (bl == 1);
}

void SQLBooleanLiteral::preAnalyze(AnalyzeContext* actx) {
}

void SQLBooleanLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}

void SQLBooleanLiteral::analyze(AnalyzeContext* actx) {
}

AnalyzedType SQLBooleanLiteral::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLBooleanLiteral::init(VirtualMachine* vm) {
}

AbstractVmInstance* SQLBooleanLiteral::interpret(VirtualMachine* vm) {
	if(vm->isSelectPlanning()){
		interpretOnPlanning(vm);
		return nullptr;
	}

	return PrimitiveReference::createBoolReference(vm, this->value ? 1 : 0);
}

void SQLBooleanLiteral::interpretOnPlanning(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	BooleanScanParam* param = new BooleanScanParam(this->value);

	planner->push(param);
}

void SQLBooleanLiteral::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	BooleanLiteralColumnParam* param = new BooleanLiteralColumnParam(this->value);
	colHolder->push(param);
}

} /* namespace alinous */
