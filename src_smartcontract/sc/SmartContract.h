/*
 * SmartContract.h
 *
 *  Created on: 2018/12/31
 *      Author: iizuka
 */

#ifndef SC_SMARTCONTRACT_H_
#define SC_SMARTCONTRACT_H_

#include "base/ArrayList.h"

namespace alinous {

class File;
class CompilationUnit;
class InputStream;
class VirtualMachine;
class AnalyzeContext;
class UnicodeString;

class SmartContract {
public:
	SmartContract();
	virtual ~SmartContract();

	void addCompilationUnit(InputStream* stream, int length);
	void analyze(VirtualMachine* vm);

	void setMainMethod(const UnicodeString* mainPackage, const UnicodeString* mainClass, const UnicodeString* mainMethod);

	void createInstance(VirtualMachine* vm);

private:
	UnicodeString* mainPackage;
	UnicodeString* mainClass;
	UnicodeString* mainMethod;
	ArrayList<CompilationUnit> progs;
	AnalyzeContext* actx;
};

} /* namespace alinous */

#endif /* SC_SMARTCONTRACT_H_ */
