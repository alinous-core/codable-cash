/*
 * AnalyzedTypeChecker.h
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_ANALYZEDTYPECHECKER_H_
#define TYPE_CHECK_ANALYZEDTYPECHECKER_H_

namespace alinous {

class AnalyzeContext;
class AbstractExpression;
class LeftType;
class RightType;
class AnalyzedType;

class AnalyzedTypeChecker {
public:
	AnalyzedTypeChecker();
	virtual ~AnalyzedTypeChecker();

	bool checkCompatibility(AnalyzeContext* actx, AbstractExpression* leftExp, AbstractExpression* rightExp);
	bool checkCompatibility(AnalyzeContext* actx, AbstractExpression* leftExp, AbstractExpression* rightExp, bool compare);

	int checkCompatibility(AnalyzeContext* actx, AnalyzedType* leftType, AnalyzedType* rightType);
private:
	LeftType* left;
	RightType* right;
};

} /* namespace alinous */

#endif /* TYPE_CHECK_ANALYZEDTYPECHECKER_H_ */
