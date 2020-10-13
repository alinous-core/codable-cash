/*
 * AbstractSQLPart.h
 *
 *  Created on: 2019/02/21
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTSQLPART_H_
#define SQL_ABSTRACTSQLPART_H_

#include "engine/sc/CodeElement.h"
#include "lang_sql/sql/ISQLElement.h"

namespace alinous {

class AbstractSQLPart : public CodeElement, public ISQLElement {
public:
	explicit AbstractSQLPart(int kind);
	virtual ~AbstractSQLPart();

	virtual bool isExecutable();
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTSQLPART_H_ */
