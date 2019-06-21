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

#include "base/UnicodeString.h"

namespace alinous {

ClassDeclare::ClassDeclare() : CodeElement(CodeElement::CLASS_DECLARE) {
	this->interface = false;
	this->block = nullptr;
	this->name = nullptr;
	this->extends = nullptr;
	this->implements = nullptr;
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
}

void ClassDeclare::preAnalyze(AnalyzeContext* actx) {
	CompilationUnit* unit = getCompilationUnit();
	PackageSpace* space = actx->getPackegeSpace(unit->getPackageName());

	AnalyzedClass* dec = space->getClass(this->name);
	if(dec != nullptr){
		actx->addValidationError(L"Class is already registered", this);

		return;
	}

	space->addClassDeclare(this);

	this->block->setParent(this);
	this->block->preAnalyze(actx);
}

void ClassDeclare::analyzeTypeRef(AnalyzeContext* actx) {
	this->block->analyzeTypeRef(actx);
}


void ClassDeclare::analyze(AnalyzeContext* actx) {
	this->block->analyze(actx);
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

} /* namespace alinous */
