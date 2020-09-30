/*
 * DeletedRecordsOidsCursor.h
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_DELETEDRECORDSOIDSCURSOR_H_
#define TRANSACTION_UPDATE_CACHE_DELETEDRECORDSOIDSCURSOR_H_

namespace alinous {
class IBtreeScanner;
}
using namespace alinous;

namespace codablecash {

class DeletedOidsRepository;
class CdbOid;

class DeletedRecordsOidsCursor {
public:
	explicit DeletedRecordsOidsCursor(DeletedOidsRepository* repo);
	virtual ~DeletedRecordsOidsCursor();

	bool hasNext() const noexcept;
	const CdbOid* next() noexcept;

private:
	IBtreeScanner* scanner;
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_DELETEDRECORDSOIDSCURSOR_H_ */
