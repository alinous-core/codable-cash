/*
 * FunctionCallExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/FunctionCallExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/ValidationError.h"

#include "sc_declare/ClassDeclare.h"
#include "sc_expression/VariableIdentifier.h"

#include "sc_analyze_functions/VTableRegistory.h"
#include "sc_analyze_functions/VTableClassEntry.h"

#include "base/UnicodeString.h"


namespace alinous {

FunctionCallExpression::FunctionCallExpression() : AbstractExpression(CodeElement::EXP_FUNCTIONCALL) {
	this->name = nullptr;
	this->strName = nullptr;
}

FunctionCallExpression::~FunctionCallExpression() {
	delete this->name;
	this->args.deleteElements();
	delete this->strName;
}

void FunctionCallExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->setParent(this);
		exp->preAnalyze(actx);
	}

	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(this->name);
	if(valId == nullptr){
		actx->addValidationError(ValidationError::CODE_WRONG_FUNC_CALL_NAME, this, L"Function identifier must be string starts with alphabet.", {});
		return;
	}

	UnicodeString* str = valId->getName();
	this->strName = new UnicodeString(str);
}

void FunctionCallExpression::analyzeTypeRef(AnalyzeContext* actx) {
}

void FunctionCallExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->analyze(actx);
	}

	AnalyzedClass* athisClass = actx->getThisClass();
	ClassDeclare* classDec = athisClass->getClassDeclare();
	const UnicodeString* fqn = classDec->getFullQualifiedName();


	VTableRegistory* vreg = actx->getVtableRegistory();
	VTableClassEntry* classEntry = vreg->getClassEntry(fqn, athisClass);

	ArrayList<AnalyzedType> typeList;
	typeList.setDeleteOnExit();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		AnalyzedType type = exp->getType(actx);
		typeList.addElement(new AnalyzedType(type));
	}

	VTableMethodEntry* methodEntry = classEntry->findEntry(this->strName, &typeList);
	// FIXME expression : analyze
}

void FunctionCallExpression::setName(AbstractExpression* exp) noexcept {
	this->name = exp;
}

void FunctionCallExpression::addArgument(AbstractExpression* exp) noexcept {
	this->args.addElement(exp);
}

int FunctionCallExpression::binarySize() const {
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

void FunctionCallExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::EXP_FUNCTIONCALL);
	this->name->toBinary(out);

	int maxLoop = this->args.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->toBinary(out);
	}
}

void FunctionCallExpression::fromBinary(ByteBuffer* in) {
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

AnalyzedType FunctionCallExpression::getType(AnalyzeContext* actx) {
	// FIXME analyze function type
	return AnalyzedType();
}

void FunctionCallExpression::init(VirtualMachine* vm) {
	int maxLoop = this->args.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->args.get(i);
		exp->init(vm);
	}
}

AbstractVmInstance* FunctionCallExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
