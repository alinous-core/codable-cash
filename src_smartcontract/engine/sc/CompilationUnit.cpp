/*
 * CompilationUnit.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "engine/sc/CompilationUnit.h"
#include "lang/sc_declare/ClassDeclare.h"
#include "lang/sc_declare/PackageDeclare.h"
#include "lang/sc_declare/ImportsDeclare.h"
#include "base/UnicodeString.h"

namespace alinous {

CompilationUnit::CompilationUnit() : classes(4), CodeElement(CodeElement::COMPILANT_UNIT) {
	this->package = nullptr;
	this->imports = nullptr;
}

CompilationUnit::~CompilationUnit() {
	delete this->package;
	delete this->imports;

	this->classes.deleteElements();
}

void CompilationUnit::preAnalyze(AnalyzeContext* actx) {
	if(this->imports != nullptr){
		this->imports->setParent(this);
		this->imports->preAnalyze(actx);
	}

	int maxLoop = this->classes.size();
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		dec->setParent(this);
		dec->preAnalyze(actx);
	}
}

void CompilationUnit::analyzeType(AnalyzeContext* actx) {
	int maxLoop = this->classes.size();
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		dec->analyzeTypeRef(actx);
	}

}

void CompilationUnit::analyze(AnalyzeContext* actx) {
	int maxLoop = this->classes.size();
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		dec->analyze(actx);
	}
}

void CompilationUnit::init(VirtualMachine* vm) {
	int maxLoop = this->classes.size();
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		dec->init(vm);
	}
}


void CompilationUnit::setPackage(PackageDeclare* package) {
	this->package = package;
}


const UnicodeString* CompilationUnit::getPackageName() noexcept {
	if(this->package == nullptr){
		return nullptr;
	}
	return this->package->getPackageName();
}


void CompilationUnit::setImports(ImportsDeclare* imports) noexcept {
	this->imports = imports;
}

void CompilationUnit::addClassDeclare(ClassDeclare* clazz) {
	this->classes.addElement(clazz);
}

ClassDeclare* CompilationUnit::getClassDeclare(int pos) const noexcept {
	return this->classes.get(pos);
}

ImportsDeclare* CompilationUnit::getImportDeclare() const noexcept {
	return this->imports;
}


int CompilationUnit::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(char);
	if(this->package){
		total += this->package->binarySize();
	}

	total += sizeof(char);
	if(this->imports){
		total += this->imports->binarySize();
	}

	total += sizeof(uint32_t);
	int maxLoop = this->classes.size();
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		total += dec->binarySize();
	}

	return total;
}

void CompilationUnit::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::COMPILANT_UNIT);

	char bl = this->package != nullptr ? (char)1 : (char)0;
	out->put(bl);

	if(this->package != nullptr){
		this->package->toBinary(out);
	}

	bl = this->imports != nullptr ? (char)1 : (char)0;
	out->put(bl);

	if(this->imports != nullptr){
		this->imports->toBinary(out);
	}

	uint32_t maxLoop = this->classes.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		dec->toBinary(out);
	}

}

void CompilationUnit::fromBinary(ByteBuffer* in) {
	char bl = in->get();
	if(bl == (char)1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::PACKAGE_DECLARE);
		this->package = dynamic_cast<PackageDeclare*>(element);
	}

	bl = in->get();
	if(bl == (char)1){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::IMPORTS_DECLARE);
		this->imports = dynamic_cast<ImportsDeclare*>(element);
	}

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkKind(element, CodeElement::CLASS_DECLARE);

		ClassDeclare* dec = dynamic_cast<ClassDeclare*>(element);
		this->classes.addElement(dec);
	}
}

} /* namespace alinous */
