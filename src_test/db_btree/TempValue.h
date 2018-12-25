/*
 * TempValue.h
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#ifndef DB_BTREE_TEMPVALUE_H_
#define DB_BTREE_TEMPVALUE_H_

#include <inttypes.h>

#include "filestore_block/IBlockObject.h"

namespace alinous {

class TempValue : public IBlockObject {
public:
	TempValue();
	virtual ~TempValue();

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);

};

} /* namespace alinous */

#endif /* DB_BTREE_TEMPVALUE_H_ */
