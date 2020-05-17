/*
 * TableObjectFactory.h
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#ifndef TABLE_TABLEOBJECTFACTORY_H_
#define TABLE_TABLEOBJECTFACTORY_H_
#include <cstdint>

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class CdbBinaryObject;

class TableObjectFactory {
public:
	static CdbBinaryObject* createFromBinary(ByteBuffer* in, uint8_t expectedType);

};

} /* namespace codablecash */

#endif /* TABLE_TABLEOBJECTFACTORY_H_ */
