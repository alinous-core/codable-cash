/*
 * AnalyzeContext.h
 *
 *  Created on: 2019/05/22
 *      Author: iizuka
 */

#ifndef SC_ANALYZECONTEXT_H_
#define SC_ANALYZECONTEXT_H_

#include "base/HashMap.h"

namespace alinous {

class VirtualMachine;
class UnicodeString;
class PackageSpace;

class AnalyzeContext {
public:
	AnalyzeContext();
	virtual ~AnalyzeContext();

	void setVm(VirtualMachine* vm) noexcept;

	PackageSpace* getPackegeSpace(const UnicodeString* spaceName) noexcept;

private:
	VirtualMachine* vm;
	HashMap<UnicodeString, PackageSpace> *packageSpaces;
};

} /* namespace alinous */

#endif /* SC_ANALYZECONTEXT_H_ */
