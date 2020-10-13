/*
 * LeftType.h
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_LEFTTYPE_H_
#define TYPE_CHECK_LEFTTYPE_H_

#include "vm/type_check/AbstractTypeCheckTarget.h"

namespace alinous {

class AbstractExpression;
class RightType;

class LeftType : public AbstractTypeCheckTarget {
public:
	explicit LeftType(AbstractExpression* exp);
	virtual ~LeftType();

	int checkTypeCompatibility(AnalyzeContext* actx, RightType* rightType, bool compare);
};

} /* namespace alinous */

#endif /* TYPE_CHECK_LEFTTYPE_H_ */
