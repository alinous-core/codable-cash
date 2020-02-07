/*
 * ConstructorCall.cpp
 *
 *  Created on: 2020/02/05
 *      Author: iizuka
 */

#include "sc_expression/ConstructorCall.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "sc_expression/VariableIdentifier.h"

#include "base/UnicodeString.h"


namespace alinous {

ConstructorCall::ConstructorCall() : AbstractExpression(CodeElement::EXP_CONSTRUCTORCALL) {
	this->name = nullptr;
	this->strName = nullptr;
	this->atype = nullptr;
}

ConstructorCall::~ConstructorCall() {
	delete this->name;
	this->args.deleteElements();

	delete this->strName;
	delete this->atype;
}

void ConstructorCall::setName(AbstractExpression* exp) noexcept {
	this->name = exp;
}

const UnicodeString* ConstructorCall::getName() noexcept {
	if(this->strName == nullptr){
		VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(this->name);
		const UnicodeString* n = valId->getName();
		this->strName = new UnicodeString(n);
	}

	return this->strName;
}

void ConstructorCall::addArgument(AbstractExpression* exp) noexcept {
	this->args.addElement(exp);
}


void ConstructorCall::init(VirtualMachine* vm) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->init(vm);
	}
}

int ConstructorCall::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += this->name->binarySize();

	total += sizeof(uint32_t);
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		total += exp->binarySize();
	}

	return total;
}

void ConstructorCall::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::EXP_CONSTRUCTORCALL);
	this->name->toBinary(out);

	int maxLoop = this->args.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->toBinary(out);
	}
}

void ConstructorCall::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->name = dynamic_cast<AbstractExpression*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkIsExp(element);
		AbstractExpression* exp = dynamic_cast<AbstractExpression*>(element);

		this->args.addElement(exp);
	}
}

void ConstructorCall::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void ConstructorCall::analyzeTypeRef(AnalyzeContext* actx) {
}

void ConstructorCall::analyze(AnalyzeContext* actx) {
	AnalyzedClass* aclass = actx->getThisClass();
	this->atype = new AnalyzedType(aclass);
}

AnalyzedType ConstructorCall::getType(AnalyzeContext* actx) {
	return *this->atype;
}


AbstractVmInstance* ConstructorCall::interpret(VirtualMachine* vm) {
	return nullptr;
}

} /* namespace alinous */
