/*
 * DdlColumnDescriptor.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "sql_ddl/DdlColumnDescriptor.h"

namespace alinous {

DdlColumnDescriptor::DdlColumnDescriptor() : AbstractSQLPart(CodeElement::DDL_COLMUN_DESC)  {
	// TODO Auto-generated constructor stub

}

DdlColumnDescriptor::~DdlColumnDescriptor() {
	// TODO Auto-generated destructor stub
}

int DdlColumnDescriptor::binarySize() const {
}

void DdlColumnDescriptor::toBinary(ByteBuffer* out) {
}

void DdlColumnDescriptor::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
