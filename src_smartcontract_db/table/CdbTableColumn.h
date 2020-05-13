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
}
using namespace alinous;

namespace codablecash {

class CdbOid;

class CdbTableColumn : public CdbBinaryObject {
public:

	explicit CdbTableColumn(uint64_t oid);
	virtual ~CdbTableColumn();

	const CdbOid* getOid() const noexcept;

	void setName(const UnicodeString* name) noexcept;
	void setType(uint8_t type, int length) noexcept;
	void setAttributes(bool notnull, bool unique) noexcept;
	void setDefaultValue(const UnicodeString* defaultValue) noexcept;
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
