/*
 * UpdatedRecordCursor.h
 *
 *  Created on: 2020/09/29
 *      Author: iizuka
 */

#ifndef TRANSACTION_UPDATE_CACHE_UPDATEDRECORDCURSOR_H_
#define TRANSACTION_UPDATE_CACHE_UPDATEDRECORDCURSOR_H_

namespace codablecash {

class UpdatedRecordsRepository;

class UpdatedRecordCursor {
public:
	explicit UpdatedRecordCursor(UpdatedRecordsRepository* repo);
	virtual ~UpdatedRecordCursor();

private:
};

} /* namespace codablecash */

#endif /* TRANSACTION_UPDATE_CACHE_UPDATEDRECORDCURSOR_H_ */
