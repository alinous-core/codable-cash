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
	if(this->package){
		delete this->package;
	}
	this->classes.deleteElements();
}

void CompilationUnit::setPackage(PackageDeclare* package) {
	this->package = package;
}

void CompilationUnit::addClassDeclare(ClassDeclare* clazz) {
	this->classes.addElement(clazz);
}

int CompilationUnit::binarySize() const {
}

void CompilationUnit::toBinary(ByteBuffer* out) {
}

void CompilationUnit::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
