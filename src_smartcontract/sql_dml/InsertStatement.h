/*
 * InsertStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_INSERTSTATEMENT_H_
#define SQL_DML_INSERTSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class InsertStatement : public AbstractSQLStatement {
public:
	InsertStatement();
	virtual ~InsertStatement();
};

} /* namespace alinous */

#endif /* SQL_DML_INSERTSTATEMENT_H_ */
