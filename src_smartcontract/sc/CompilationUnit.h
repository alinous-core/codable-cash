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
class PackageDeclare;
class AnalyzeContext;

class CompilationUnit : public CodeElement {
public:
	CompilationUnit();
	virtual ~CompilationUnit();

	void preAnalyze(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void setPackage(PackageDeclare* package);
	void addClassDeclare(ClassDeclare* clazz);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	PackageDeclare* package;
	ArrayList<ClassDeclare> classes;
};

} /* namespace alinous */

#endif /* SC_COMPILATIONUNIT_H_ */
