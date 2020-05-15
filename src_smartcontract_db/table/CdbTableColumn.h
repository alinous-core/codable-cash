/*
 * CdbTableColumn.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef TABLE_CDBTABLECOLUMN_H_
#define TABLE_CDBTABLECOLUMN_H_
#include <cstdint>

#include "engine/CdbBinaryObject.h"

namespace alinous {
class UnicodeString;
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class CdbOid;
class SchemaObjectIdPublisher;

class CdbTableColumn : public CdbBinaryObject {
public:
	static const constexpr uint8_t CDB_OBJ_TYPE{2};

	static const constexpr uint8_t COLUMN_TYPE_VARCHAR{1};
	static const constexpr uint8_t COLUMN_TYPE_TEXT{2};
	static const constexpr uint8_t COLUMN_TYPE_INT{3};

	explicit CdbTableColumn(uint64_t oid);
	virtual ~CdbTableColumn();

	const CdbOid* getOid() const noexcept;

	void setName(const UnicodeString* name) noexcept;
	const UnicodeString* getName() const noexcept;
	void setType(uint8_t type, int length) noexcept;
	void setAttributes(bool notnull, bool unique) noexcept;
	void setDefaultValue(const UnicodeString* defaultValue) noexcept;

	void assignNewOid(SchemaObjectIdPublisher* publisher);
	void setOid(uint64_t oid) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);
private:
	CdbOid* oid;

	UnicodeString* name;
	uint8_t type;
	int length;
	bool notnull;
	bool unique;
	UnicodeString* defaultValue;
};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLECOLUMN_H_ */