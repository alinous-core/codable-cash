/*
 * AbstractTypeCheckTarget.h
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_ABSTRACTTYPECHECKTARGET_H_
#define TYPE_CHECK_ABSTRACTTYPECHECKTARGET_H_

namespace alinous {

class AbstractExpression;

class AbstractTypeCheckTarget {
public:
	explicit AbstractTypeCheckTarget(AbstractExpression* exp);
	virtual ~AbstractTypeCheckTarget();

protected:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* TYPE_CHECK_ABSTRACTTYPECHECKTARGET_H_ */
