/*
 * AbstractJoinPart.h
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTJOINPART_H_
#define SQL_ABSTRACTJOINPART_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class AbstractJoinPart : public AbstractSQLExpression {
public:
	explicit AbstractJoinPart(int kind);
	virtual ~AbstractJoinPart();
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTJOINPART_H_ */
