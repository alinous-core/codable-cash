/*
 * IJoinRightSource.h
 *
 *  Created on: 2020/08/23
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_JOIN_IJOINRIGHTSOURCE_H_
#define TRANSACTION_SCANNER_JOIN_IJOINRIGHTSOURCE_H_

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

class CdbRecord;
class AbstractCdbKey;

class IJoinRightSource : public IJoinLeftSource {
public:
	IJoinRightSource();
	virtual ~IJoinRightSource();

	virtual void reset(const AbstractCdbKey* key) = 0;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_JOIN_IJOINRIGHTSOURCE_H_ */
