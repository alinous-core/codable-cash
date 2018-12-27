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
#include "btree/AbstractBtreeDataFactory.h"

namespace alinous {

class TempValue : public IBlockObject {
public:
	TempValue();
	virtual ~TempValue();

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);

};

class TmpValueFactory : public AbstractBtreeDataFactory {
public:
	virtual ~TmpValueFactory();
};

} /* namespace alinous */

#endif /* DB_BTREE_TEMPVALUE_H_ */
