/*
 * AlterAddColumnCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_

#include "lang_sql/sql_ddl_alter/AbstractAlterDdlWithTypeDesc.h"

namespace codablecash {
class TableStore;
}
using namespace codablecash;

namespace alinous {

class DdlColumnDescriptor;

class AlterAddColumnCommand : public AbstractAlterDdlWithTypeDesc {
public:
	AlterAddColumnCommand(const AlterAddColumnCommand& inst);
	AlterAddColumnCommand();
	virtual ~AlterAddColumnCommand();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId);

private:
	void checkRecordCount(TableStore* store);
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_ */
