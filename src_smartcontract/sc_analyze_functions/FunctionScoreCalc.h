/*
 * FunctionScoreCalc.h
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_
#define SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_

namespace alinous {

class MethodScore;

class FunctionScoreCalc {
public:
	FunctionScoreCalc();
	virtual ~FunctionScoreCalc();

private:
	MethodScore* topScore;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_ */
