/*
 * InsertRecordsCacheCursor.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_INSERTRECORDSCACHECURSOR_H_
#define TRANSACTION_UPDATE_CACHE_INSERTRECORDSCACHECURSOR_H_

namespace alinous {
class IBtreeScanner;
}
using namespace alinous;

namespace codablecash {

class CdbRecord;
class InsertedRecordsRepository;

class InsertRecordsCacheCursor {
public:
	explicit InsertRecordsCacheCursor(InsertedRecordsRepository* insertsRepo);
	virtual ~InsertRecordsCacheCursor();

	bool hasNext() const noexcept;
	const CdbRecord* next() noexcept;

private:
	IBtreeScanner* scanner;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_INSERTRECORDSCACHECURSOR_H_ */
