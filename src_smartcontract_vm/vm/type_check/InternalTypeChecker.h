/*
 * InternalTypeChecker.h
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_INTERNALTYPECHECKER_H_
#define TYPE_CHECK_INTERNALTYPECHECKER_H_

namespace alinous {

class AnalyzedType;

class InternalTypeChecker {
public:
	static constexpr int NO_CHECK{-1};
	static constexpr int OK{0};
	static constexpr int WARN_PRECISION{1};
	static constexpr int INCOMPATIBLE{2};

	static int analyzeCompatibility(AnalyzedType* leftType, AnalyzedType* rightType);


private:
	static int checkRightNull(AnalyzedType* leftType, AnalyzedType* rightType);

	static int checkDomValue(AnalyzedType* leftType, AnalyzedType* rightType);
	static int checkDomObject(AnalyzedType* leftType, AnalyzedType* rightType);
	static int checkObject(AnalyzedType* leftType, AnalyzedType* rightType);
	static int checkBool(AnalyzedType* leftType, AnalyzedType* rightType);
	static int checkPrimitive(AnalyzedType* leftType, AnalyzedType* rightType);
	static int checkString(AnalyzedType* leftType, AnalyzedType* rightType);
};

} /* namespace alinous */

#endif /* TYPE_CHECK_INTERNALTYPECHECKER_H_ */
