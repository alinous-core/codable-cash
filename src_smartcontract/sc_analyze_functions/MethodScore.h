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

private:
	VTableMethodEntry* method;
	bool match;
	int score;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_FUNCTIONS_METHODSCORE_H_ */
