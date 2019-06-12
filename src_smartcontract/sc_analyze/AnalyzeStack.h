/*
 * AnalyzeStack.h
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZESTACK_H_
#define SC_ANALYZE_ANALYZESTACK_H_

#include "base/ArrayList.h"

namespace alinous {

class AnalyzedStackReference;

class AnalyzeStack {
public:
	AnalyzeStack(bool functionStack);
	virtual ~AnalyzeStack();

private:
	bool functionStack;
	ArrayList<AnalyzedStackReference> variables;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZESTACK_H_ */
