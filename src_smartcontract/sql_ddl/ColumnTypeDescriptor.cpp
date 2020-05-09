/*
 * ColumnTypeDescriptor.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "sql_ddl/ColumnTypeDescriptor.h"

namespace alinous {

ColumnTypeDescriptor::ColumnTypeDescriptor() : AbstractSQLPart(CodeElement::DDL_TYPE_DESC) {
	// TODO Auto-generated constructor stub

}

ColumnTypeDescriptor::~ColumnTypeDescriptor() {
	// TODO Auto-generated destructor stub
}

int ColumnTypeDescriptor::binarySize() const {
}

void ColumnTypeDescriptor::toBinary(ByteBuffer* out) {
}

void ColumnTypeDescriptor::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
