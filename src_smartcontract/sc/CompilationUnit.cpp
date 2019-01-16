/*
 * CompilationUnit.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc/CompilationUnit.h"
#include "sc_declare/ClassDeclare.h"

namespace codablecash {

CompilationUnit::CompilationUnit() : classes(4), CodeElement(CodeElement::COMPILANT_UNIT) {

}

CompilationUnit::~CompilationUnit() {
	this->classes.deleteElements();
}

void CompilationUnit::addClassDeclare(ClassDeclare* clazz) {
	this->classes.addElement(clazz);
}

} /* namespace codablecash */
