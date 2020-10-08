/*
 * AlterModifyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlWithTypeDesc.h"

namespace codablecash {
class AlterModifyCommandLog;
}
using namespace codablecash;

namespace alinous {

class DdlColumnDescriptor;
class VirtualMachine;

class AlterModifyCommand : public AbstractAlterDdlWithTypeDesc {
public:
	AlterModifyCommand(const AlterModifyCommand& inst);
	AlterModifyCommand();
	virtual ~AlterModifyCommand();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId);

private:
	void validate(VirtualMachine* vm, AlterModifyCommandLog* log, TableIdentifier* tableId);

};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_ */
