/*
 * AlterAddColumnCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterAddColumnCommand : public AbstractAlterDdlCommand {
public:
	explicit AlterAddColumnCommand();
	virtual ~AlterAddColumnCommand();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_ */
