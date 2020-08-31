/*
 * FunctionCallScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/FunctionCallScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "scan_condition/IValueProvider.h"

namespace codablecash {

FunctionCallScanCondition::FunctionCallScanCondition(const FunctionCallScanCondition& inst) : AbstractScanCondition(CodeElement::SQL_EXP_FUNCTION_CALL) {
	this->name = new UnicodeString(inst.name);

	int maxLoop = inst.arguments.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* value = inst.arguments.get(i);

		this->arguments.addElement(value->clone());
	}

	this->str = nullptr;
}

FunctionCallScanCondition::FunctionCallScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_FUNCTION_CALL) {
	this->name = nullptr;

	this->str = nullptr;
}

FunctionCallScanCondition::~FunctionCallScanCondition() {
	delete this->name;
	this->arguments.deleteElements();

	resetStr();
}

void FunctionCallScanCondition::setName(UnicodeString* name) noexcept {
	this->name = name;
	resetStr();
}

void FunctionCallScanCondition::addArgument(IValueProvider* arg) noexcept {
	this->arguments.addElement(arg);
	resetStr();
}

const UnicodeString* FunctionCallScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();

		this->str = new UnicodeString(L"");

		this->str->append(this->name);

		this->str->append(L"(");

		int maxLoop = this->arguments.size();
		for(int i = 0; i != maxLoop; ++i){
			if(i > 0){
				this->str->append(L", ");
			}

			IValueProvider* value = this->arguments.get(i);
			AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(value);
			this->str->append(el->toStringCode());
		}

		this->str->append(L")");
	}

	return this->str;
}

void FunctionCallScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void FunctionCallScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->arguments.size();

	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* value = this->arguments.get(i);

		value->analyzeConditions(vm, planner);
	}
}

IValueProvider* FunctionCallScanCondition::clone() const noexcept {
	return new FunctionCallScanCondition(*this);
}

} /* namespace codablecash */
