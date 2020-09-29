/*
 * UpdatedRecordCursor.h
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_UPDATEDRECORDCURSOR_H_
#define TRANSACTION_UPDATE_CACHE_UPDATEDRECORDCURSOR_H_

namespace alinous {
class IBtreeScanner;
}
using namespace alinous;

namespace codablecash {

class UpdatedRecordsRepository;
class CdbRecord;

class UpdatedRecordCursor {
public:
	explicit UpdatedRecordCursor(UpdatedRecordsRepository* repo);
	virtual ~UpdatedRecordCursor();

	bool hasNext() const noexcept;
	const CdbRecord* next() noexcept;

private:
	IBtreeScanner* scanner;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_UPDATEDRECORDCURSOR_H_ */
