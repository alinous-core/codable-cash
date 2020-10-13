/*
 * AlterTableStatement.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTERTABLESTATEMENT_H_
#define SQL_DDL_ALTERTABLESTATEMENT_H_

#include "lang_sql/sql/AbstractSQLStatement.h"

namespace alinous {

class TableIdentifier;
class AbstractAlterDdlCommand;

class AlterTableStatement : public AbstractSQLStatement {
public:
	AlterTableStatement();
	virtual ~AlterTableStatement();

	void setTableId(TableIdentifier* tableId) noexcept;
	void setCommand(AbstractAlterDdlCommand* cmd) noexcept;

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);

	AbstractAlterDdlCommand* getCmd() const noexcept {
		return cmd;
	}

	const TableIdentifier* getTableId() const noexcept {
		return tableId;
	}

private:
	TableIdentifier* tableId;
	AbstractAlterDdlCommand* cmd;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTERTABLESTATEMENT_H_ */
