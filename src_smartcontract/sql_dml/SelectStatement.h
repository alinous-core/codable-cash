/*
 * SelectStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_SELECTSTATEMENT_H_
#define SQL_DML_SELECTSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class SelectStatement : public AbstractSQLStatement {
public:
	SelectStatement();
	virtual ~SelectStatement();
};

} /* namespace alinous */

#endif /* SQL_DML_SELECTSTATEMENT_H_ */
