/*
 * ClassDeclare.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc_declare/ClassDeclare.h"
#include "sc_declare/ClassDeclareBlock.h"
#include "sc/CompilationUnit.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/PackageSpace.h"

#include "base/UnicodeString.h"

namespace alinous {

ClassDeclare::ClassDeclare() : CodeElement(CodeElement::CLASS_DECLARE) {
	this->block = nullptr;
	this->name = nullptr;
}

ClassDeclare::~ClassDeclare() {
	if(this->block != nullptr){
		delete this->block;
	}
	if(this->name != nullptr){
		delete this->name;
	}
}

void ClassDeclare::preAnalyze(AnalyzeContext* actx) {
	CompilationUnit* unit = getCompilationUnit();
	PackageSpace* space = actx->getPackegeSpace(unit->getPackageName());

	ClassDeclare* dec = space->getClass(this->name);
	if(dec != nullptr){
		// FIXME add class error
		return;
	}

	space->addClassDeclare(this);

	this->block->setParent(this);
	this->block->preAnalyze(actx);
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
}

void ClassDeclare::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	uint8_t bl = in->get();
	if(bl == 1){
		CodeElement* element = CodeElement::createFromBinary(in);
		checkKind(element, CodeElement::CLASS_DECLARE_BLOCK);
		this->block = dynamic_cast<ClassDeclareBlock*>(element);
	}
}

} /* namespace alinous */
