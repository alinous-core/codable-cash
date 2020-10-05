/*
 * Schema.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef SCHEMA_SCHEMA_H_
#define SCHEMA_SCHEMA_H_
#include <cstdint>

#include "engine/CdbBinaryObject.h"
#include "base/ArrayList.h"
#include "base/HashMap.h"

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class CdbOid;
class CdbTable;

class Schema : public CdbBinaryObject {
public:
	static const constexpr uint8_t CDB_OBJ_TYPE{4};
	explicit Schema(uint64_t oid);
	virtual ~Schema();

	//void setOid(uint64_t oid) noexcept;
	void setName(UnicodeString* name) noexcept;
	const UnicodeString* getName() const noexcept {
		return name;
	}

	void renameTable(const UnicodeString* lastName, const UnicodeString* newName) noexcept;

	void addTable(CdbTable* table) noexcept;
	CdbTable* getCdbTableByName(const UnicodeString* tableName) const noexcept;
	const ArrayList<CdbTable>* getTablesList() const noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);

private:
	CdbOid* oid;
	UnicodeString* name;

	ArrayList<CdbTable>* tables;
	HashMap<UnicodeString, CdbTable> nameTableMap;
	HashMap<CdbOid, CdbTable> oidTableMap;
};

} /* namespace codablecash */

#endif /* SCHEMA_SCHEMA_H_ */
