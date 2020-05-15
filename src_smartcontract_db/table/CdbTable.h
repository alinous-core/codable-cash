/*
 * CdbTable.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef TABLE_CDBTABLE_H_
#define TABLE_CDBTABLE_H_

#include <cstdint>

#include "base/ArrayList.h"
#include "base/HashMap.h"

#include "engine/CdbBinaryObject.h"

namespace alinous {
class ByteBuffer;
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class CdbTableColumn;
class CdbOid;
class SchemaObjectIdPublisher;
class CdbTableIndex;

class CdbTable : public CdbBinaryObject {
public:
	static const constexpr uint8_t CDB_OBJ_TYPE{1};

	explicit CdbTable(uint64_t oid);
	virtual ~CdbTable();

	void addColumn(uint8_t oid, const wchar_t* name, uint8_t type, int length, bool notnull, bool unique, const wchar_t* defaultValue) noexcept;
	void addColumn(uint8_t oid, const UnicodeString* name, uint8_t type, int length, bool notnull, bool unique, const UnicodeString* defaultValue) noexcept;
	void addColumn(CdbTableColumn* col) noexcept;

	CdbTableColumn* getColumn(const wchar_t* name) noexcept;
	CdbTableColumn* getColumn(const UnicodeString* name) noexcept;

	CdbTableColumn* findColumnByOid(const CdbOid* oid) const noexcept;

	void assignNewOid(SchemaObjectIdPublisher* publisher);
	void setOid(uint64_t oid) noexcept;

	void setName(UnicodeString* name) noexcept;

	void setPrimaryKey(const wchar_t* col);
	void setPrimaryKey(const UnicodeString* colstr);
	void setPrimaryKeys(ArrayList<const UnicodeString>* cols);

	void addIndex(CdbTableIndex* index);
	CdbTableIndex* getIndexByColumnOid(const CdbOid* oid) const noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);
private:
	CdbOid* oid;

	UnicodeString* name;
	ArrayList<CdbTableColumn>* columns;
	HashMap<CdbOid, CdbTableColumn>* columnMap;

	ArrayList<CdbTableIndex>* indexes;

};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLE_H_ */
