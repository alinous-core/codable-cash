/*
 * DropTableStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DDL_DROPTABLESTATEMENT_H_
#define SQL_DDL_DROPTABLESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class DropTableStatement : public AbstractSQLStatement {
public:
	DropTableStatement();
	virtual ~DropTableStatement();
};

} /* namespace alinous */

#endif /* SQL_DDL_DROPTABLESTATEMENT_H_ */
