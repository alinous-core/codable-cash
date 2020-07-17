/*
 * MethodScore.h
 *
 *  Created on: 2019/11/18
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_FUNCTIONS_METHODSCORE_H_
#define SC_ANALYZE_FUNCTIONS_METHODSCORE_H_

#include "base/ArrayList.h"

namespace alinous {

class VTableMethodEntry;
class AnalyzedType;

class MethodScore {
public:
	explicit MethodScore(VTableMethodEntry* method);
	virtual ~MethodScore();

	void eveluate(ArrayList<AnalyzedType>* types) noexcept;
	int getScore() const noexcept;
	bool isMatch() const noexcept;

	VTableMethodEntry* getEntry() const noexcept;

private:
	bool evaluateTypeScore(AnalyzedType* base, AnalyzedType* arg) noexcept;

	bool evaluateObjectTypeScore(AnalyzedType* base, AnalyzedType* arg) noexcept;
	bool evaluateDomObjectTypeScore(AnalyzedType* base, AnalyzedType* arg) noexcept;
	bool evaluateBoolTypeScore(AnalyzedType* arg) noexcept;
	bool evaluateByteTypeScore(AnalyzedType* arg) noexcept;
	bool evaluateCharTypeScore(AnalyzedType* arg) noexcept;
	bool evaluateShortTypeScore(AnalyzedType* arg) noexcept;
	bool evaluateIntTypeScore(AnalyzedType* arg) noexcept;
	bool evaluateLongTypeScore(AnalyzedType* arg) noexcept;
	bool evaluateStringTypeScore(AnalyzedType* arg) noexcept;

private:
	bool doEvaluateObjectTypeScore(AnalyzedType* base, AnalyzedType* arg) noexcept;
private:
	VTableMethodEntry* method;
	bool match;
	int score;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_METHODSCORE_H_ */
