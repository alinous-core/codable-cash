/*
 * RecordObjectIdPublisher.h
 *
 *  Created on: 2020/05/29
 *      Author: iizuka
 */

#ifndef TRANSACTION_RECORDOBJECTIDPUBLISHER_H_
#define TRANSACTION_RECORDOBJECTIDPUBLISHER_H_

#include <cstdint>

namespace codablecash {

class SchemaManager;

class RecordObjectIdPublisher {
public:
	explicit RecordObjectIdPublisher(SchemaManager* schema);
	virtual ~RecordObjectIdPublisher();

	uint64_t newOid() noexcept;
	void saveSchema();
private:
	SchemaManager* schema;
};

} /* namespace codablecash */

#endif /* TRANSACTION_RECORDOBJECTIDPUBLISHER_H_ */
