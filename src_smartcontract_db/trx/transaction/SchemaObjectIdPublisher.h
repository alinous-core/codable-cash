/*
 * SchemaObjectIdPublisher.h
 *
 *  Created on: 2020/05/14
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCHEMAOBJECTIDPUBLISHER_H_
#define TRANSACTION_SCHEMAOBJECTIDPUBLISHER_H_
#include <cstdint>

namespace codablecash {
class SchemaManager;

class SchemaObjectIdPublisher {
public:
	explicit SchemaObjectIdPublisher(SchemaManager* schema);
	virtual ~SchemaObjectIdPublisher();

	uint64_t newOid();
	void saveSchema();

	uint64_t getSchemaObjectVersionId() const noexcept;
private:
	SchemaManager* schema;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCHEMAOBJECTIDPUBLISHER_H_ */
