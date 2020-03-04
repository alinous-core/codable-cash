/*
 * ClassDeclare.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"
#include "sc_declare/ClassImplements.h"
#include "sc_declare/ClassExtends.h"

#include "sc/CompilationUnit.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/PackageSpace.h"
#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"


namespace alinous {

ClassDeclare::ClassDeclare() : CodeElement(CodeElement::CLASS_DECLARE) {
	this->interface = false;
	this->block = nullptr;
	this->name = nullptr;
	this->extends = nullptr;
	this->implements = nullptr;
	this->inheritIndex = -1;
	this->fqn = nullptr;
}

ClassDeclare::~ClassDeclare() {
	if(this->block != nullptr){
		delete this->block;
	}
	if(this->name != nullptr){
		delete this->name;
	}
	delete this->extends;
	delete this->implements;
	delete this->fqn;
}

void ClassDeclare::preAnalyze(AnalyzeContext* actx) {
	if(!this->interface){
		addDefaultConstructor();
	}


	CompilationUnit* unit = getCompilationUnit();
	PackageSpace* space = actx->getPackegeSpace(unit->getPackageName());

	AnalyzedClass* dec = space->getClass(this->name);
	if(dec != nullptr){
		actx->addValidationError(ValidationError::CODE_CLASS_ALREADY_EXISTS, this, L"Class {0} is already registered", {this->name});

		return;
	}

	space->addClassDeclare(this);

	if(this->extends != nullptr){
		this->extends->setParent(this);
		this->extends->preAnalyze(actx);
	}
	if(this->implements != nullptr){
		this->implements->setParent(this);
		this->implements->preAnalyze(actx);
	}

	this->block->setParent(this);
	this->block->preAnalyze(actx);
}


void ClassDeclare::addDefaultConstructor() noexcept {
	this->block->addDefaultConstructor(this->name);
}


void ClassDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->extends != nullptr){
		this->extends->analyzeTypeRef(actx);
	}
	if(this->implements != nullptr){
		this->implements->analyzeTypeRef(actx);
	}

	if(actx->hasError()){
		return;
	}

	CompilationUnit* unit = getCompilationUnit();
	PackageSpace* space = actx->getPackegeSpace(unit->getPackageName());
	AnalyzedClass* dec = space->getClass(this->name);

	// set analyzed class
	if(this->extends != nullptr){
		AnalyzedType* cls = this->extends->getAnalyzedType();
		dec->setExtends(cls->getAnalyzedClass());
	}

	if(this->implements != nullptr){
		const ArrayList<AnalyzedType>* list = this->implements->getAnalyzedTypes();

		int maxLoop = list->size();
		for(int i = 0; i != maxLoop; ++i){
			AnalyzedType* cls = list->get(i);
			dec->addImplements(cls->getAnalyzedClass());
		}
	}

	this->block->analyzeTypeRef(actx);
}


void ClassDeclare::analyze(AnalyzeContext* actx) {
	this->block->analyze(actx);
}

void ClassDeclare::init(VirtualMachine* vm) {
	this->block->init(vm);
}

void ClassDeclare::setBlock(ClassDeclareBlock* block) noexcept {
	this->block = block;
}

void alinous::ClassDeclare::setName(UnicodeString* name) noexcept {
	this->name = name;
}

const UnicodeString* ClassDeclare::getName() noexcept {
	return this->name;
}


const UnicodeString* ClassDeclare::getFullQualifiedName() noexcept {
	if(this->fqn == nullptr){
		this->fqn = new UnicodeString(L"");

		const UnicodeString* package = getPackageName();
		if(package != nullptr){
			this->fqn->append(package);
			this->fqn->append(L".");
		}

		this->fqn->append(this->name);
	}

	return this->fqn;
}


int ClassDeclare::binarySize() const {
	checkNotNull(this->block);
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	total += stringSize(this->name);
	total += sizeof(uint8_t);
	if(this->block != nullptr){
		total += this->block->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->extends != nullptr){
		total += this->extends->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->implements != nullptr){
		total += this->implements->binarySize();
	}

	return total;
}

void ClassDeclare::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);
	checkNotNull(this->block);

	out->putShort(CodeElement::CLASS_DECLARE);

	putString(out, this->name);

	out->put(this->block != nullptr ? (uint8_t)1 : (uint8_t)0);
	if(this->block != nullptr){
		this->block->toBinary(out);
	}

	out->put(this->extends != nullptr ? (uint8_t)1 : (uint8_t)0);
	if(this->extends != nullptr){
		this->extends->toBinary(out);
	}

	out->put(this->implements != nullptr ? (uint8_t)1 : (uint8_t)0);
	if(this->implements != nullptr){
		this->implements->toBinary(out);
	}
}

void ClassDeclare::setExtends(ClassExtends* extends) noexcept {
	this->extends = extends;
}

void ClassDeclare::setImplements(ClassImplements* implements) noexcept {
	this->implements = implements;
}

void ClassDeclare::setInterface(bool interface) noexcept {
	this->interface = interface;
}

void ClassDeclare::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	uint8_t bl = in->get();
	if(bl == 1){
		CodeElement* element = CodeElement::createFromBinary(in);
		checkKind(element, CodeElement::CLASS_DECLARE_BLOCK);
		this->block = dynamic_cast<ClassDeclareBlock*>(element);
	}

	bl = in->get();
	if(bl == 1){
		CodeElement* element = CodeElement::createFromBinary(in);
		checkKind(element, CodeElement::CLASS_EXTENDS);
		this->extends = dynamic_cast<ClassExtends*>(element);
	}

	bl = in->get();
	if(bl == 1){
		CodeElement* element = CodeElement::createFromBinary(in);
		checkKind(element, CodeElement::CLASS_IMPLEMENTS);
		this->implements = dynamic_cast<ClassImplements*>(element);
	}
}

ClassDeclare* ClassDeclare::getBaseClass() const noexcept {
	if(this->extends == nullptr){
		return nullptr;
	}
	AnalyzedType* type = this->extends->getAnalyzedType();
	AnalyzedClass* aclazz = type->getAnalyzedClass();

	return aclazz->getClassDeclare();
}

int ClassDeclare::getInheritIndex() const noexcept {
	return this->inheritIndex;
}

void ClassDeclare::setInheritIndex(int inheritIndex) noexcept {
	this->inheritIndex = inheritIndex;
}

ArrayList<MethodDeclare>* ClassDeclare::getMethods() noexcept {
	return this->block->getMethods();
}

ArrayList<MemberVariableDeclare>* ClassDeclare::getMemberVariables() noexcept {
	return this->block->getMemberVariables();
}


} /* namespace alinous */
