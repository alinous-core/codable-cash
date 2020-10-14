/*
 * SQLLikeExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLLikeExpression.h"
#include "lang_sql/sql_expression/SQLLiteral.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/exp/LikeScanCondition.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_exp/LikeExpressionScanColumnTarget.h"


namespace alinous {

SQLLikeExpression::SQLLikeExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_LIKE) {
	this->left = nullptr;
	this->right = nullptr;
	this->escape = nullptr;
}

SQLLikeExpression::~SQLLikeExpression() {
	delete this->left;
	delete this->right;
	delete this->escape;
}

void SQLLikeExpression::setLeft(AbstractSQLExpression* left) noexcept {
	this->left = left;
}

void SQLLikeExpression::setRight(SQLLiteral* right) noexcept {
	this->right = right;
}

void SQLLikeExpression::setEscape(SQLLiteral* escape) noexcept {
	this->escape = escape;
}

int SQLLikeExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();

	total += sizeof(uint8_t);
	if(this->escape != nullptr){
		total += this->escape->binarySize();
	}

	return total;
}

void SQLLikeExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::SQL_EXP_LIKE);
	this->left->toBinary(out);
	this->right->toBinary(out);

	out->put(this->escape != nullptr ? 1 : 0);
	if(this->escape != nullptr){
		this->escape->toBinary(out);
	}
}

void SQLLikeExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_LITERAL);
	this->right = dynamic_cast<SQLLiteral*>(element);

	uint8_t bl = in->get();
	if(bl == 1){
		element = createFromBinary(in);
		checkKind(element, CodeElement::SQL_EXP_LITERAL);
		this->escape = dynamic_cast<SQLLiteral*>(element);
	}
}

void SQLLikeExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->right->setParent(this);
	this->right->preAnalyze(actx);

	if(this->escape != nullptr){
		this->escape->preAnalyze(actx);
	}
}

void SQLLikeExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->right->analyzeTypeRef(actx);

	if(this->escape != nullptr){
		this->escape->analyzeTypeRef(actx);
	}
}

void SQLLikeExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->right->analyze(actx);

	if(this->escape != nullptr){
		this->escape->analyze(actx);
	}
}

AnalyzedType SQLLikeExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLLikeExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->right->init(vm);

	if(this->escape != nullptr){
		this->escape->init(vm);
	}
}

AbstractVmInstance* SQLLikeExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	LikeScanCondition* cond = new LikeScanCondition();
	planner->push(cond);

	AbstractScanConditionElement* element = nullptr;
	IValueProvider* val = nullptr;

	this->left->interpret(vm);
	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setLeft(val);

	this->right->interpret(vm);
	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setRight(val);

	if(this->escape != nullptr){
		this->escape->interpret(vm);
		element = planner->pop();
		val = ScanConditionCast::toIValueProvider(element, vm, this);
		cond->setEscape(val);
	}

	return nullptr;
}

void SQLLikeExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	LikeExpressionScanColumnTarget* cond = new LikeExpressionScanColumnTarget();
	colHolder->push(cond);

	this->left->onSelectTarget(vm);
	AbstractScanColumnsTarget* col = colHolder->pop();
	cond->setLeft(col);

	this->right->onSelectTarget(vm);
	col = colHolder->pop();
	cond->setRight(col);

	if(this->escape != nullptr){
		this->escape->onSelectTarget(vm);
		col = colHolder->pop();
		cond->setEscape(col);
	}
}

} /* namespace alinous */
