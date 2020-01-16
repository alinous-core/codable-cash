/*
 * AnalyzedThisClassStackPopper.h
 *
 *  Created on: 2020/01/16
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZEDTHISCLASSSTACKPOPPER_H_
#define SC_ANALYZE_ANALYZEDTHISCLASSSTACKPOPPER_H_

namespace alinous {

class AnalyzeContext;
class AnalyzedClass;

class AnalyzedThisClassStackPopper {
public:
	AnalyzedThisClassStackPopper(AnalyzeContext* actx, AnalyzedClass* thisClass);
	virtual ~AnalyzedThisClassStackPopper();

private:
	AnalyzeContext* actx;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDTHISCLASSSTACKPOPPER_H_ */
