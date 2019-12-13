/*
 * FunctionScoreCalc.h
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_
#define SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_

#include "base/ArrayList.h"

namespace alinous {

class UnicodeString;
class MethodScore;
class MethodDeclare;
class VTableClassEntry;
class AnalyzedType;

class FunctionScoreCalc {
public:
	FunctionScoreCalc(VTableClassEntry* classEntry);
	virtual ~FunctionScoreCalc();


	MethodScore* findMethod(const UnicodeString* methodName, ArrayList<AnalyzedType>* types) noexcept;
private:
	VTableClassEntry* classEntry;

	MethodScore* topScore;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_ */
