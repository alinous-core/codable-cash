/*
 * AbstractAlterDdlWithTypeDesc.h
 *
 *  Created on: 2020/10/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ABSTRACTALTERDDLWITHTYPEDESC_H_
#define SQL_DDL_ALTER_ABSTRACTALTERDDLWITHTYPEDESC_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AbstractAlterDdlWithTypeDesc : public AbstractAlterDdlCommand {
public:
	explicit AbstractAlterDdlWithTypeDesc(short kind);
	virtual ~AbstractAlterDdlWithTypeDesc();

protected:
	DdlColumnDescriptor* copyColumnDescriptor(DdlColumnDescriptor* columnDescriptor) const;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ABSTRACTALTERDDLWITHTYPEDESC_H_ */
