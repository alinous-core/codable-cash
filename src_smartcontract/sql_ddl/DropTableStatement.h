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
class TableIdentifier;

class DropTableStatement : public AbstractSQLStatement {
public:
	DropTableStatement();
	virtual ~DropTableStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setTableId(TableIdentifier* tableId) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	TableIdentifier* tableId;
};

} /* namespace alinous */

#endif /* SQL_DDL_DROPTABLESTATEMENT_H_ */
