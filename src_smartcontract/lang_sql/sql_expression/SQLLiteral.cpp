/*
 * SQLLiteral.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLLiteral.h"

#include "base/UnicodeString.h"
#include "base/Long.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_string/VmStringInstance.h"

#include "base/StackRelease.h"

#include "scan_select/scan_condition/params/AbstractScanConditionParameter.h"
#include "scan_select/scan_condition/params/NumericScanParam.h"
#include "scan_select/scan_condition/params/StringScanParam.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_params/NumberLiteralColumnParam.h"
#include "scan_select/scan_columns/scan_columns_params/StringLiteralColumnParam.h"


namespace alinous {

SQLLiteral::SQLLiteral() :
		AbstractSQLExpression(CodeElement::SQL_EXP_LITERAL) {
	this->value = nullptr;
	this->type = TYPE_STRING;
	this->longv = 0;
	this->stringValue = nullptr;
}

SQLLiteral::~SQLLiteral() {
	delete this->value;
	delete this->stringValue;
}

void SQLLiteral::setValue(UnicodeString* value, uint8_t type) noexcept {
	this->value = value;
	this->type = type;
}

int SQLLiteral::binarySize() const {
	checkNotNull(this->value);

	int total = sizeof(uint16_t);
	total += stringSize(this->value);
	total += sizeof(uint8_t);

	return total;
}

void SQLLiteral::toBinary(ByteBuffer* out) {
	checkNotNull(this->value);

	out->putShort(CodeElement::SQL_EXP_LITERAL);
	putString(out, this->value);
	out->put(this->type);
}

void SQLLiteral::fromBinary(ByteBuffer* in) {
	this->value = getString(in);
	this->type = in->get();
}

void SQLLiteral::preAnalyze(AnalyzeContext* actx) {
}

void SQLLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}

void SQLLiteral::analyze(AnalyzeContext* actx) {
	if (this->type == SQLLiteral::TYPE_NUMBER) {
		this->longv = Long::parseLong(this->value);
		return;
	}

	this->stringValue = this->value->substring(1, this->value->length() - 1);
}

AnalyzedType SQLLiteral::getType(AnalyzeContext* actx) {
	if (this->type == SQLLiteral::TYPE_NUMBER) {
		return AnalyzedType(AnalyzedType::TYPE_LONG);
	}

	return AnalyzedType(AnalyzedType::TYPE_STRING);
}

void SQLLiteral::init(VirtualMachine* vm) {

}

AbstractVmInstance* SQLLiteral::interpret(VirtualMachine* vm) {
	if (vm->isSelectPlanning()) {
		interpretOnPlanning(vm);
		return nullptr;
	}

	if (this->type == SQLLiteral::TYPE_NUMBER) {
		return PrimitiveReference::createLongReference(vm, this->longv);
	}

	VmStringInstance* inst = new (vm) VmStringInstance(vm, this->stringValue);
	return inst;
}

void SQLLiteral::interpretOnPlanning(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	AbstractScanConditionParameter* param = nullptr;
	if (this->type == SQLLiteral::TYPE_NUMBER) {
		param = new NumericScanParam(this->longv);
	} else {
		param = new StringScanParam(this->stringValue);
	}

	planner->push(param);
}

void SQLLiteral::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	AbstractColumnParam* param = nullptr;
	if (this->type == SQLLiteral::TYPE_NUMBER) {
		param = new NumberLiteralColumnParam(this->longv);
	} else {
		param = new StringLiteralColumnParam(this->stringValue);
	}

	colHolder->push(param);
}

} /* namespace alinous */
