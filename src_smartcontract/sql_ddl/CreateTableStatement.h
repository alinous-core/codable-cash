/*
 * CreateTableStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DDL_CREATETABLESTATEMENT_H_
#define SQL_DDL_CREATETABLESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class CreateTableStatement : public AbstractSQLStatement {
public:
	CreateTableStatement();
	virtual ~CreateTableStatement();
};

} /* namespace alinous */

#endif /* SQL_DDL_CREATETABLESTATEMENT_H_ */
