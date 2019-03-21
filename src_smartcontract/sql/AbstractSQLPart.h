/*
 * AbstractSQLPart.h
 *
 *  Created on: 2019/02/21
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTSQLPART_H_
#define SQL_ABSTRACTSQLPART_H_

#include "sc/CodeElement.h"
#include "sql/ISQLElement.h"

namespace alinous {

class AbstractSQLPart : public CodeElement, public ISQLElement {
public:
	explicit AbstractSQLPart(int kind);
	virtual ~AbstractSQLPart();
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTSQLPART_H_ */
