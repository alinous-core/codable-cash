/*
 * AnalyzeStackPopper.h
 *
 *  Created on: 2019/06/29
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZESTACKPOPPER_H_
#define SC_ANALYZE_ANALYZESTACKPOPPER_H_

namespace alinous {

class AnalyzeStackManager;

class AnalyzeStackPopper {
public:
	AnalyzeStackPopper(AnalyzeStackManager* stack, bool func);
	virtual ~AnalyzeStackPopper();


private:
	AnalyzeStackManager* stack;
	bool func;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZESTACKPOPPER_H_ */
