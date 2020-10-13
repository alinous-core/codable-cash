/*
 * CompilationUnit.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_COMPILATIONUNIT_H_
#define SC_COMPILATIONUNIT_H_

#include "engine/sc/CodeElement.h"
#include "base/ArrayList.h"

namespace alinous {

class ClassDeclare;
class PackageDeclare;
class ImportsDeclare;
class AnalyzeContext;
class UnicodeString;
class VirtualMachine;

class CompilationUnit : public CodeElement {
public:
	CompilationUnit();
	virtual ~CompilationUnit();

	void preAnalyze(AnalyzeContext* actx);
	void analyzeType(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);
	void init(VirtualMachine* vm);

	void setPackage(PackageDeclare* package);
	void setImports(ImportsDeclare* imports) noexcept;
	void addClassDeclare(ClassDeclare* clazz);
	ClassDeclare* getClassDeclare(int pos) const noexcept;

	const UnicodeString* getPackageName() noexcept;

	ImportsDeclare* getImportDeclare() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	PackageDeclare* package;
	ImportsDeclare* imports;
	ArrayList<ClassDeclare> classes;
};

} /* namespace alinous */

#endif /* SC_COMPILATIONUNIT_H_ */
