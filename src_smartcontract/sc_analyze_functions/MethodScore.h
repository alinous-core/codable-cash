/*
 * MethodScore.h
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_METHODSCORE_H_
#define SC_ANALYZE_FUNCTIONS_METHODSCORE_H_

namespace alinous {

class MethodDeclare;

class MethodScore {
public:
	MethodScore();
	virtual ~MethodScore();

private:
	MethodDeclare* method;
	int score;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_METHODSCORE_H_ */
