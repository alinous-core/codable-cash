/*
 * CdbTableIdentifier.h
 *
 *  Created on: 2020/05/29
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_CDBTABLEIDENTIFIER_H_
#define TABLE_RECORD_CDBTABLEIDENTIFIER_H_

#include "engine/CdbBinaryObject.h"

namespace alinous {
class UnicodeString;
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class CdbTableIdentifier : public CdbBinaryObject {
public:
	CdbTableIdentifier(const CdbTableIdentifier& inst);
	CdbTableIdentifier();
	CdbTableIdentifier(const wchar_t* scheme, const wchar_t* table);
	virtual ~CdbTableIdentifier();

	const UnicodeString* getSchema() const noexcept {
		return schema;
	}
	void setSchema(UnicodeString* schema) noexcept;

	const UnicodeString* getTable() const noexcept {
		return table;
	}
	void setTable(UnicodeString* table) noexcept;

	int binarySize() const;
	void toBinary(ByteBuffer* out) const;
	static CdbTableIdentifier* fromBinary(ByteBuffer* in);


private:
	UnicodeString* schema;
	UnicodeString* table;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBTABLEIDENTIFIER_H_ */
