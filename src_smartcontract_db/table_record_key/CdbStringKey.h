/*
 * CdbStringKey.h
 *
 *  Created on: 2020/05/21
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_KEY_CDBSTRINGKEY_H_
#define TABLE_RECORD_KEY_CDBSTRINGKEY_H_

#include "table_record_key/AbstractCdbKey.h"
#include "base/UnicodeString.h"

namespace codablecash {

class CdbStringKey : public AbstractCdbKey {
public:
	CdbStringKey();
	virtual ~CdbStringKey();

	virtual AbstractBtreeKey* clone()  const noexcept;
	virtual int compareTo(const AbstractBtreeKey* key) const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

private:
	static UnicodeString::ValueCompare cmp;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_KEY_CDBSTRINGKEY_H_ */
