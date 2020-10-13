/*
 * TableObjectFactory.cpp
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#include "table/TableObjectFactory.h"
#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"
#include "table/CdbTableIndex.h"

#include "schema/Schema.h"

#include "engine/CdbBinaryObject.h"
#include "engine/CdbException.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

CdbBinaryObject* TableObjectFactory::createFromBinary(ByteBuffer* in, uint8_t expectedType) {
	uint8_t type = in->get();
	uint64_t oid;
	CdbBinaryObject* obj = nullptr;

	if(expectedType != type){
		throw new CdbException(L"Wrong binary format with wrong object type.", __FILE__, __LINE__);
	}

	switch(type){
	case CdbTable::CDB_OBJ_TYPE:
		oid = in->getLong();
		obj = new CdbTable(oid);
		break;
	case CdbTableColumn::CDB_OBJ_TYPE:
		oid = in->getLong();
		obj = new CdbTableColumn(oid);
		break;
	case CdbTableIndex::CDB_OBJ_TYPE:
		oid = in->getLong();
		obj = new CdbTableIndex(oid);
		break;
	case Schema::CDB_OBJ_TYPE:
		oid = in->getLong();
		obj = new Schema(oid);
		break;
	default:
		throw new CdbException(L"Wrong binary format with wrong object type.", __FILE__, __LINE__);
	}

	return obj;
}


} /* namespace codablecash */
