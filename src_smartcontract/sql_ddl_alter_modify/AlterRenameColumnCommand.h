/*
 * AlterRenameColumnCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterRenameColumnCommand : public AbstractAlterDdlCommand {
public:
	AlterRenameColumnCommand();
	virtual ~AlterRenameColumnCommand();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMAND_H_ */
