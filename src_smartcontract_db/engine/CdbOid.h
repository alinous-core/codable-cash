/*
 * CdbOid.h
 *
 *  Created on: 2020/05/13
 *      Author: iizuka
 */

#ifndef ENGINE_CDBOID_H_
#define ENGINE_CDBOID_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"

namespace alinous {
class IBlockObject;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey;

class CdbOid : public IBlockObject {
public:
	static const constexpr uint8_t CDB_OID{100};
	static const constexpr uint8_t CDB_LOCAL_OID{101};

	CdbOid(const CdbOid& inst);
	explicit CdbOid(uint64_t oid);
	virtual ~CdbOid();

	virtual uint8_t getTypeCode() const noexcept;
	virtual bool isLocal() const noexcept;
	virtual bool equals(const CdbOid* other) const noexcept;

	virtual CdbOid* copy() const noexcept;
	virtual IBlockObject* copyData() const noexcept;
	AbstractCdbKey* toKey() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static CdbOid* fromBinary(ByteBuffer* in);

	uint64_t getOidValue() const noexcept {
		return oid;
	}

	int hashCode() const;

	class ValueCompare {
	public:
		int operator() (const CdbOid* const _this, const  CdbOid* const object) const noexcept;
	};
private:
	uint64_t oid;
};

} /* namespace codablecash */

#endif /* ENGINE_CDBOID_H_ */
