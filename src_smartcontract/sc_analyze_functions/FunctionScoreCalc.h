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
	static constexpr int ERROR_NOT_EXIST = 1;
	static constexpr int ERROR_AMBIGOUS = 1;

	FunctionScoreCalc(VTableClassEntry* classEntry);
	virtual ~FunctionScoreCalc();

	MethodScore* findMethod(const UnicodeString* methodName, ArrayList<AnalyzedType>* types) noexcept;
	int getErrorCode() const noexcept;
	ArrayList<MethodScore>* getAmbigousList() noexcept;
private:
	void newScore(MethodScore* score) noexcept;
private:
	VTableClassEntry* classEntry;

	MethodScore* topScore;
	int errorCode;
	ArrayList<MethodScore> list;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_FUNCTIONSCORECALC_H_ */
