/*
 * CompilationUnit.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc/CompilationUnit.h"
#include "sc_declare/ClassDeclare.h"
#include "sc_declare/PackageDeclare.h"

namespace alinous {

CompilationUnit::CompilationUnit() : classes(4), CodeElement(CodeElement::COMPILANT_UNIT) {
	this->package = nullptr;
}

CompilationUnit::~CompilationUnit() {
	delete this->package;

	this->classes.deleteElements();
}

void CompilationUnit::setPackage(PackageDeclare* package) {
	this->package = package;
}

void CompilationUnit::addClassDeclare(ClassDeclare* clazz) {
	this->classes.addElement(clazz);
}

int CompilationUnit::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(char);
	if(this->package){
		total += this->package->binarySize();
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

	char bl = 0;
	if(this->package != nullptr){
		out->put((char)1);
		this->package->toBinary(out);
	}
	else{
		out->put((char)0);
	}

	uint32_t maxLoop = this->classes.size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		ClassDeclare* dec = this->classes.get(i);
		dec->toBinary(out);
	}

}

void CompilationUnit::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
