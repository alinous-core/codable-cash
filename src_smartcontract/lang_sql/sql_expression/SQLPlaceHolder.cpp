/*
 * SQLPlaceHolder.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLPlaceHolder.h"
#include "lang/sc_expression/AbstractExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_condition/params/PlaceHolderScanCondition.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_exp/PlaceHolderScanColumnTarget.h"


using codablecash::SelectScanPlanner;
namespace alinous {

SQLPlaceHolder::SQLPlaceHolder() : AbstractSQLExpression(CodeElement::SQL_EXP_PLACE_HOLDER) {
	this->exp = nullptr;
}

SQLPlaceHolder::~SQLPlaceHolder() {
	delete this->exp;
}

void SQLPlaceHolder::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int SQLPlaceHolder::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLPlaceHolder::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_PLACE_HOLDER);
	this->exp->toBinary(out);
}

void SQLPlaceHolder::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void SQLPlaceHolder::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLPlaceHolder::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLPlaceHolder::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

AnalyzedType SQLPlaceHolder::getType(AnalyzeContext* actx) {
	//return this->exp->getType(actx);
	return AnalyzedType();
}

void SQLPlaceHolder::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLPlaceHolder::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	PlaceHolderScanCondition* cond = new PlaceHolderScanCondition(this->exp);
	planner->push(cond);

	return nullptr;
}

void SQLPlaceHolder::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	PlaceHolderScanColumnTarget* cond = new PlaceHolderScanColumnTarget(this->exp);
	colHolder->push(cond);
}



} /* namespace alinous */
