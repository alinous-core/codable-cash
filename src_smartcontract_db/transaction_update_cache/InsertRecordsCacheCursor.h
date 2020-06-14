/*
 * InsertRecordsCacheCursor.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_INSERTRECORDSCACHECURSOR_H_
#define TRANSACTION_UPDATE_CACHE_INSERTRECORDSCACHECURSOR_H_

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class CdbRecord;

class InsertRecordsCacheCursor {
public:
	InsertRecordsCacheCursor(const ArrayList<CdbRecord>* insertedRecords);
	virtual ~InsertRecordsCacheCursor();

	bool hasNext() const noexcept;
	const CdbRecord* next() noexcept;
private:
	const ArrayList<CdbRecord>* insertedRecords;
	int position;
	int limit;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_INSERTRECORDSCACHECURSOR_H_ */
