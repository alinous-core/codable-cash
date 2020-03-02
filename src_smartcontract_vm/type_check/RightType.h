/*
 * RightType.h
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_RIGHTTYPE_H_
#define TYPE_CHECK_RIGHTTYPE_H_

#include "type_check/AbstractTypeCheckTarget.h"

namespace alinous {

class RightType : public AbstractTypeCheckTarget {
public:
	explicit RightType(AbstractExpression* exp);
	virtual ~RightType();
};

} /* namespace alinous */

#endif /* TYPE_CHECK_RIGHTTYPE_H_ */
