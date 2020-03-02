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
	static constexpr int OK{0};
	static constexpr int WARN_PRECISION{1};
	static constexpr int INCOMPATIBLE{2};

	static int analyzeCompatibility(AnalyzedType* leftType, AnalyzedType* rightType);
};

} /* namespace alinous */

#endif /* TYPE_CHECK_INTERNALTYPECHECKER_H_ */
