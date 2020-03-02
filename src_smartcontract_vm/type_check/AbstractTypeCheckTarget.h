/*
 * AbstractTypeCheckTarget.h
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#ifndef TYPE_CHECK_ABSTRACTTYPECHECKTARGET_H_
#define TYPE_CHECK_ABSTRACTTYPECHECKTARGET_H_

namespace alinous {

class AnalyzeContext;
class AbstractExpression;
class AnalyzedType;
class UnicodeString;

class AbstractTypeCheckTarget {
public:
	explicit AbstractTypeCheckTarget(AbstractExpression* exp);
	virtual ~AbstractTypeCheckTarget();

	virtual void init(AnalyzeContext* actx);
	AnalyzedType* getAnalyzedType() const noexcept;

	const UnicodeString* toString() noexcept;

protected:
	AbstractExpression* exp;
	AnalyzedType* atype;
	mutable UnicodeString* str;
};

} /* namespace alinous */

#endif /* TYPE_CHECK_ABSTRACTTYPECHECKTARGET_H_ */
