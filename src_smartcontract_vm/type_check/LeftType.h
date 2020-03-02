/*
 * LeftType.h
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_LEFTTYPE_H_
#define TYPE_CHECK_LEFTTYPE_H_

#include "type_check/AbstractTypeCheckTarget.h"

namespace alinous {

class AbstractExpression;

class LeftType : public AbstractTypeCheckTarget {
public:
	explicit LeftType(AbstractExpression* exp);
	virtual ~LeftType();
};

} /* namespace alinous */

#endif /* TYPE_CHECK_LEFTTYPE_H_ */
