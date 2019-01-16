/*
 * CompilationUnit.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_COMPILATIONUNIT_H_
#define SC_COMPILATIONUNIT_H_

#include "sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {

class ClassDeclare;

class CompilationUnit : public CodeElement {
public:
	CompilationUnit();
	virtual ~CompilationUnit();

	void addClassDeclare(ClassDeclare* clazz);

private:
	ArrayList<ClassDeclare> classes;
};

} /* namespace alinous */

#endif /* SC_COMPILATIONUNIT_H_ */
