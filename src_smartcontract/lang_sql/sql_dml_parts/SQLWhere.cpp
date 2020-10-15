/*
 * SQLWhere.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "lang_sql/sql_dml_parts/SQLWhere.h"
#include "lang_sql/sql/AbstractSQLExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolder.h"

#include "scan_select/scan_condition/base/RootScanCondition.h"
#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "vm/VirtualMachine.h"

using namespace codablecash;

namespace alinous {

SQLWhere::SQLWhere() : AbstractSQLPart(CodeElement::SQL_PART_WHERE) {
	this->exp = nullptr;
}

SQLWhere::~SQLWhere() {
	delete this->exp;
}

void alinous::SQLWhere::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLWhere::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLWhere::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLWhere::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);
	if(at.getType() != AnalyzedType::TYPE_BOOL){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"Not expression requires boolean value.", {});
	}
}

void SQLWhere::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLWhere::interpret(VirtualMachine* vm) {
	this->exp->interpret(vm);

	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolder* cholder = planner->getConditions();
	RootScanCondition* root = cholder->getRoot();

	AbstractScanConditionElement* element = cholder->pop();

	AbstractScanCondition* cond = ScanConditionCast::toAbstractScanCondition(element, vm, this);
	root->addCondition(cond);

	return nullptr;
}

int SQLWhere::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLWhere::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_PART_WHERE);
	this->exp->toBinary(out);
}

void SQLWhere::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

} /* namespace alinous */
