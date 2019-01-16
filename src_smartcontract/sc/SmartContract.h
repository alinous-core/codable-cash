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

class SmartContract {
public:
	SmartContract();
	virtual ~SmartContract();

	void addCompilationUnit(InputStream* stream, int length);

private:
	ArrayList<CompilationUnit> progs;
};

} /* namespace alinous */

#endif /* SC_SMARTCONTRACT_H_ */
