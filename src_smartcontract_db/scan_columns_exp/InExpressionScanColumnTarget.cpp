/*
 * InExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/InExpressionScanColumnTarget.h"

#include "scan_columns_exp/ExpressionListScanColumnTarget.h"

#include "instance_exception/TypeCastExceptionClassDeclare.h"
#include "instance_exception/ExceptionInterrupt.h"

namespace codablecash {

InExpressionScanColumnTarget::InExpressionScanColumnTarget() {
	this->left = nullptr;
	this->list = nullptr;
}

InExpressionScanColumnTarget::~InExpressionScanColumnTarget() {
	delete this->left;
	delete this->list;
}

void InExpressionScanColumnTarget::setLeft(AbstractScanColumnsTarget* cond) noexcept {
	this->left = cond;
}

void InExpressionScanColumnTarget::setList(ExpressionListScanColumnTarget* list) noexcept {
	this->list = list;
}

ExpressionListScanColumnTarget* InExpressionScanColumnTarget::castToExpressionListScanColumnTarget(AbstractScanColumnsTarget* col, VirtualMachine* vm, const CodeElement* element) {
	ExpressionListScanColumnTarget* val = dynamic_cast<ExpressionListScanColumnTarget*>(col);

	if(val == nullptr){
		delete col;

		TypeCastExceptionClassDeclare::throwException(vm, element);
		ExceptionInterrupt::interruptPoint(vm);
	}

	return val;
}

const UnicodeString* InExpressionScanColumnTarget::toStringCode() noexcept {
	// FIXME toStringCode()
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");
	}

	return this->str;
}

} /* namespace codablecash */
