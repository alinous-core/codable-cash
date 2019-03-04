/*
 * RollbackStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_ROLLBACKSTATEMENT_H_
#define SQL_DML_ROLLBACKSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class RollbackStatement : public AbstractSQLStatement {
public:
	RollbackStatement();
	virtual ~RollbackStatement();
};

} /* namespace alinous */

#endif /* SQL_DML_ROLLBACKSTATEMENT_H_ */
