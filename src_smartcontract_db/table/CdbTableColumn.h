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
class AlterModifyCommand;
}
using namespace alinous;

namespace codablecash {

class CdbOid;
class SchemaObjectIdPublisher;
class ScanResultFieldMetadata;
class CdbTable;
class ColumnModifyContext;

class CdbTableColumn : public CdbBinaryObject {
public:
	static const constexpr uint8_t CDB_OBJ_TYPE{2};

	CdbTableColumn(const CdbTableColumn& inst);
	explicit CdbTableColumn(uint64_t oid);
	virtual ~CdbTableColumn();

	const CdbOid* getOid() const noexcept;

	void setName(const UnicodeString* name) noexcept;
	const UnicodeString* getName() const noexcept;
	void setType(uint8_t type, int length) noexcept;
	void setAttributes(bool notnull, bool unique) noexcept;
	void setDefaultValue(const UnicodeString* defaultValue) noexcept;

	bool isUnique() const noexcept {
		return unique;
	}
	bool isNotnull() const noexcept {
		return notnull;
	}
	int getLength() const noexcept {
		return length;
	}

	void assignNewOid(SchemaObjectIdPublisher* publisher);
	void setOid(uint64_t oid) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	void fromBinary(ByteBuffer* in);

	int getPosition() const noexcept;
	void setPosition(int position) noexcept;

	uint8_t getType() const noexcept {
		return this->type;
	}

	ScanResultFieldMetadata* getFieldMetadata(const CdbTable* table) const noexcept;

	ColumnModifyContext* createModifyContextwithChange(const AlterModifyCommand* cmd, const UnicodeString* defaultStr);

private:
	CdbOid* oid;

	UnicodeString* name;
	uint8_t type;
	int length;
	bool notnull;
	bool unique;
	UnicodeString* defaultValue;

	int position;
};

} /* namespace codablecash */

#endif /* TABLE_CDBTABLECOLUMN_H_ */
