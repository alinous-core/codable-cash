/*
 * AlterModifyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class DdlColumnDescriptor;
class VirtualMachine;

class AlterModifyCommand : public AbstractAlterDdlCommand {
public:
	AlterModifyCommand(const AlterModifyCommand& inst);
	AlterModifyCommand();
	virtual ~AlterModifyCommand();

	void setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept;
	const DdlColumnDescriptor* getColumnDescriptor() const noexcept {
		return columnDescriptor;
	}

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();



	void interpretType(VirtualMachine* vm);

private:
	DdlColumnDescriptor* columnDescriptor;

};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERMODIFYCOMMAND_H_ */
