/*
 * CdbKeyFactory.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_CDBKEYFACTORY_H_
#define TABLE_RECORD_CDBKEYFACTORY_H_

#include "btreekey/BtreeKeyFactory.h"

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class CdbKeyFactory : public BtreeKeyFactory {
public:
	CdbKeyFactory();
	virtual ~CdbKeyFactory();

	virtual AbstractBtreeKey* fromBinary(uint32_t keyType, ByteBuffer* in) const;

	virtual BtreeKeyFactory* copy() const noexcept;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBKEYFACTORY_H_ */
