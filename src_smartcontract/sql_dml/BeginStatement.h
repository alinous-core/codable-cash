/*
 * BeginStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_BEGINSTATEMENT_H_
#define SQL_DML_BEGINSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {

class BeginStatement : public AbstractSQLStatement {
public:
	BeginStatement();
	virtual ~BeginStatement();
};

} /* namespace alinous */

#endif /* SQL_DML_BEGINSTATEMENT_H_ */
