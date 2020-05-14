/*>s
 * CdbTable.cpp
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#include "table/CdbTable.h"
#include "table/CdbTableColumn.h"

#include "engine/CdbOid.h"

#include "base/UnicodeString.h"

#include "base_io/ByteBuffer.h"

#include "transaction/SchemaObjectIdPublisher.h"

#include "table/TableObjectFactory.h"

namespace codablecash {

CdbTable::CdbTable(uint64_t oid) {
	this->columns = new ArrayList<CdbTableColumn>();
	this->columnMap = new HashMap<CdbOid, CdbTableColumn>();
	this->oid = new CdbOid(oid);
}

CdbTable::~CdbTable() {
	delete this->columnMap;

	this->columns->deleteElements();
	delete this->columns;
	delete this->oid;
}

void CdbTable::addColumn(uint8_t oid, const wchar_t* name,
		uint8_t type, int length, bool notnull, bool unique, const wchar_t* defaultValue) noexcept {
	UnicodeString strName(name);
	UnicodeString* strDefaultValue = nullptr;

	if(defaultValue != nullptr){
		strDefaultValue = new UnicodeString(defaultValue);
	}

	addColumn(oid, &strName, type, length, notnull, unique, strDefaultValue);
}

void CdbTable::addColumn(uint8_t oid, const UnicodeString* name, uint8_t type, int length,
		bool notnull, bool unique, const UnicodeString* defaultValue) noexcept {
	CdbTableColumn* col = new CdbTableColumn(oid);
	col->setName(name);
	col->setType(type, length);
	col->setAttributes(notnull, unique);
	col->setDefaultValue(defaultValue);

	addColumn(col);
}

void CdbTable::addColumn(CdbTableColumn* col) noexcept {
	this->columns->addElement(col);
	const CdbOid* o = col->getOid();
	this->columnMap->put(o, col);
}

void CdbTable::assignNewOid(SchemaObjectIdPublisher* publisher) {
	uint64_t oid = publisher->newOid();
	setOid(oid);

	int maxLoop = this->columns->size();
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		col->assignNewOid(publisher);
	}
}

void CdbTable::setOid(uint64_t oid) noexcept {
	delete this->oid;
	this->oid = new CdbOid(oid);
}


int CdbTable::binarySize() const {
	int total = sizeof(uint8_t);

	total += sizeof(uint64_t); // oid

	int maxLoop = this->columns->size();
	total += sizeof(int32_t);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		total += col->binarySize();
	}

	return total;
}

void CdbTable::toBinary(ByteBuffer* out) const {
	out->put(CdbTable::CDB_OBJ_TYPE);

	out->put(this->oid->getOid());

	int maxLoop = this->columns->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		CdbTableColumn* col = this->columns->get(i);

		col->toBinary(out);
	}

}

void CdbTable::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){

	}
}

} /* namespace codablecash */
