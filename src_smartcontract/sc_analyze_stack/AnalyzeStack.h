/*
 * AnalyzeStack.h
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZESTACK_H_
#define SC_ANALYZE_ANALYZESTACK_H_

#include "base/ArrayList.h"
#include "base/HashMap.h"

namespace alinous {

class AnalyzedStackReference;
class UnicodeString;
class AnalyzedStackReference;

class AnalyzeStack {
public:
	AnalyzeStack(bool functionStack);
	virtual ~AnalyzeStack();

	void addVariableDeclare(AnalyzedStackReference* ref) noexcept;
	bool isFunctionStack() const noexcept;

	int findStackPosOfVariable(const UnicodeString* name) const noexcept;

	AnalyzedStackReference* get(int pos) const noexcept;
private:
	bool functionStack;
	ArrayList<AnalyzedStackReference> variables;
	HashMap<UnicodeString, AnalyzedStackReference> map;


};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZESTACK_H_ */
