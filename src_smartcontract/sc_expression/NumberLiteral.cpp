/*
 * NumberLiteral.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/NumberLiteral.h"
#include "base/UnicodeString.h"
#include "base/Integer.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/RefereceFactory.h"
#include "instance_gc/GcManager.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/VmRootReference.h"
#include "instance_ref/PrimitiveReference.h"

namespace alinous {

const UnicodeString NumberLiteral::l(L"l");
const UnicodeString NumberLiteral::L(L"L");

NumberLiteral::NumberLiteral() : AbstractExpression(CodeElement::EXP_NUMBER_LITERAL) {
	this->str = nullptr;
	this->value = 0;
	this->referene = nullptr;
}

NumberLiteral::~NumberLiteral() {
	delete this->str;
	this->referene = nullptr;
}

void NumberLiteral::preAnalyze(AnalyzeContext* actx) {

}

void NumberLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}


void NumberLiteral::analyze(AnalyzeContext* actx) {
	if(this->str->endsWith(&this->L) || this->str->endsWith(&this->l)){
		// FIXME L
		this->atype = AnalyzedType(AnalyzedType::TYPE_LONG);
	}
	else{
		this->value = Integer::parseInt(this->str);
		this->atype = AnalyzedType(AnalyzedType::TYPE_INT);
	}

}

void NumberLiteral::setValue(UnicodeString* str) noexcept {
	this->str = str;
}

int NumberLiteral::binarySize() const {
	checkNotNull(this->str);

	int total = sizeof(uint16_t);
	total += stringSize(this->str);

	return total;
}

void NumberLiteral::toBinary(ByteBuffer* out) {
	checkNotNull(this->str);

	out->putShort(CodeElement::EXP_NUMBER_LITERAL);
	putString(out, this->str);
}

void NumberLiteral::fromBinary(ByteBuffer* in) {
	this->str = getString(in);
}

AnalyzedType NumberLiteral::getType() {
	return this->atype;
}

void NumberLiteral::init(VirtualMachine* vm) {
	this->referene = RefereceFactory::createNumericReference(this->value, this->atype.getType(), vm);

	VmRootReference* rootRef = vm->getVmRootReference();
	this->referene = rootRef->newNumericConstReferenece(this->value, this->atype.getType(), vm);
}

AbstractVmInstance* NumberLiteral::interpret(VirtualMachine* vm) {
	return this->referene;
}

} /* namespace alinous */
