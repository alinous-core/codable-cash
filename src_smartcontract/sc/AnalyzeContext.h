/*
 * AnalyzeContext.h
 *
 *  Created on: 2019/05/22
 *      Author: iizuka
 */

#ifndef SC_ANALYZECONTEXT_H_
#define SC_ANALYZECONTEXT_H_

namespace alinous {

class VirtualMachine;

class AnalyzeContext {
public:
	AnalyzeContext();
	virtual ~AnalyzeContext();

	void setVm(VirtualMachine* vm) noexcept;

private:
	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* SC_ANALYZECONTEXT_H_ */
