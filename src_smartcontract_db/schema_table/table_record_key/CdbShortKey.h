/*
 * CdbShortKey.h
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_CDBSHORTKEY_H_
#define TABLE_RECORD_KEY_CDBSHORTKEY_H_

#include "schema_table/table_record_key/AbstractCdbKey.h"

namespace codablecash {

class CdbShortKey : public AbstractCdbKey {
public:
	CdbShortKey(const CdbShortKey& inst);
	explicit CdbShortKey(int16_t value);
	CdbShortKey();
	virtual ~CdbShortKey();

	virtual AbstractBtreeKey* clone() const noexcept;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	int16_t getValue() const noexcept {
		return value;
	}

private:
	int16_t value;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_CDBSHORTKEY_H_ */
