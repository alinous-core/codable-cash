/*
 * CdbDataFactory.h
 *
 *  Created on: 2020/05/20
 *      Author: iizuka
 */

#ifndef TABLE_RECORD_CDBDATAFACTORY_H_
#define TABLE_RECORD_CDBDATAFACTORY_H_

#include "btree/AbstractBtreeDataFactory.h"

using namespace alinous;

namespace codablecash {

class CdbDataFactory : public AbstractBtreeDataFactory {
public:
	CdbDataFactory();
	virtual ~CdbDataFactory();

	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in);

	AbstractBtreeDataFactory* copy() const noexcept;
};

} /* namespace codablecash */

#endif /* TABLE_RECORD_CDBDATAFACTORY_H_ */
