/*
 * CdbTableIndex.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef TABLE_CDBTABLEINDEX_H_
#define TABLE_CDBTABLEINDEX_H_
#include <cstdint>

#include "base/ArrayList.h"
#include "base/HashMap.h"

#include "engine/CdbBinaryObject.h"

using namespace alinous;

namespace codablecash {

class CdbOid;
class CdbTable;
class CdbTableColumn;
class SchemaObjectIdPublisher;

class CdbTableIndex : public CdbBinaryObject {
public:
	static const constexpr uint8_t CDB_OBJ_TYPE{3};

	explicit CdbTableIndex(uint64_t oid);
	virtual ~CdbTableIndex();

	void assignNewOid(SchemaObjectIdPublisher* publisher);
	void setOid(uint64_t oid) noexcept;
	const CdbOid* getOid() const noexcept {
		return oid;
	}

	bool hasColumnOid(const CdbOid* colOid) const noexcept;

	void addColumn(CdbTableColumn* col) noexcept;

	void setPrimaryKey(bool bl);
	bool isPrimaryKey() const noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in, CdbTable* table);
private:
	CdbOid* oid;
	bool primary;

	ArrayList<CdbTableColumn>* columns;
	HashMap<CdbOid, CdbTableColumn>* columnMap;
};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLEINDEX_H_ */